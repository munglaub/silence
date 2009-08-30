#include "gui/richtextfind.h"
#include <QMessageBox>


RichTextFind::RichTextFind(QTextEdit *editor, QWidget *parent)
	: QWidget(parent)
{
	this->editor = editor;
	isFirstTime = true;

	layout = new QHBoxLayout;
	layout->setAlignment(Qt::AlignLeft);
	layout->setContentsMargins(0, 0, 0, 0);

	findEdit = new QLineEdit;
	layout->addWidget(findEdit);

	findBtn = new QPushButton(tr("Find"));
	findBtn->setFlat(true);
	connect(findBtn, SIGNAL(clicked()), this, SLOT(findit()));
	layout->addWidget(findBtn);

	hideFind = new QPushButton(QIcon("icons/window-close.png"), "");
	hideFind->setFlat(true);
	connect(hideFind, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideFind);
	setLayout(layout);

	connect(findEdit, SIGNAL(returnPressed()), findBtn, SLOT(click()));
}

RichTextFind::~RichTextFind()
{
	delete hideFind;
	delete findBtn;
	delete findEdit;
	delete layout;
}

void RichTextFind::hide()
{
	unhighlighte();
	QWidget::hide();
}

void RichTextFind::show()
{
	findEdit->setFocus(Qt::ShortcutFocusReason);
	QWidget::show();
}

void RichTextFind::unhighlighte()
{
	if (isFirstTime == false)
	{
		editor->document()->undo();
		isFirstTime = true;
	}
}

void RichTextFind::findit()
{
	QString searchString = findEdit->text();
	QTextDocument *doc = editor->document();

	bool found = false;

	if (isFirstTime == false)
		doc->undo();

	if (searchString == "")
	{
		QMessageBox::information(this, tr("Empty Search Field"),
		"The search field is empty. Please enter a word and click Find.");
	} else {
		QTextCursor highlightCursor(doc);
		QTextCursor cursor(doc);

		cursor.beginEditBlock();

		QTextCharFormat plainFormat(highlightCursor.charFormat());
		QTextCharFormat colorFormat = plainFormat;
		colorFormat.setForeground(Qt::red);

		while (!highlightCursor.isNull() && !highlightCursor.atEnd()) 
		{
			highlightCursor = doc->find(searchString, highlightCursor);

			if (!highlightCursor.isNull()) 
			{
				found = true;
				highlightCursor.mergeCharFormat(colorFormat);
			}
		}

		cursor.endEditBlock();
		isFirstTime = false;

		if (found == false) 
		{
			QMessageBox::information(this, tr("Word Not Found"),
			"Sorry, the word cannot be found.");
		}
	 }
}


