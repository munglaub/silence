#include "gui/texteditfind.h"
#include <QMessageBox>

TextEditFind::TextEditFind(QsciScintilla *editor, QWidget *parent)
	: QWidget(parent)
{
	this->editor = editor;
	
	layout = new QHBoxLayout;
	layout->setAlignment(Qt::AlignLeft);
	layout->setContentsMargins(0, 0, 0, 0);

	findEdit = new QLineEdit;
	layout->addWidget(findEdit);

	nextBtn = new QPushButton(QIcon("icons/go-next.png"), tr("Next"));
	nextBtn->setFlat(true);
	connect(nextBtn, SIGNAL(clicked()), this, SLOT(findNext()));
	layout->addWidget(nextBtn);
	
	prevBtn = new QPushButton(QIcon("icons/go-previous.png"), tr("Previous"));
	prevBtn->setFlat(true);
	connect(prevBtn, SIGNAL(clicked()), this, SLOT(findPrevious()));
	layout->addWidget(prevBtn);

	caseCbx = new QCheckBox("Match case");
	layout->addWidget(caseCbx);
	wordCbx = new QCheckBox("Match whole word");
	layout->addWidget(wordCbx);

	hideBtn = new QPushButton(QIcon("icons/window-close.png"), "");
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn);
	setLayout(layout);
	
	connect(findEdit, SIGNAL(returnPressed()), nextBtn, SLOT(click()));
}

TextEditFind::~TextEditFind()
{
	delete findEdit;
	delete nextBtn;
	delete prevBtn;
	delete hideBtn;
	delete caseCbx;
	delete wordCbx;
	delete layout;
}

void TextEditFind::show()
{
	findEdit->setFocus(Qt::ShortcutFocusReason);
	QWidget::show();
}

void TextEditFind::findNext()
{
	find(true);
}


void TextEditFind::findPrevious()
{
	find(false);
}

void TextEditFind::find(bool forward)
{
	if (findEdit->text() == "")
	{
		QMessageBox::information(this, tr("Empty Search Field"),
		"The search field is empty. Please enter a word and click Find.");
	} else {
		bool regex = false;
		bool caseSensitive = caseCbx->isChecked();
		bool wholeWord = wordCbx->isChecked();
		bool wrap = true;
		int line = -1;
		int index = -1;
		if (forward == false)
		{
			editor->getCursorPosition(&line, &index);
			--index;
		}
		bool show = true;
		if (!editor->findFirst(findEdit->text(), regex, caseSensitive, wholeWord, wrap, forward, line, index, show))
		{
			QMessageBox::information(this, tr("Word Not Found"),
			"Sorry, the word cannot be found.");
		}
	}
}


