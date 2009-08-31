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

	findBtn = new QPushButton(QIcon("icons/go-next.png"), tr("Find"));
	findBtn->setFlat(true);
	connect(findBtn, SIGNAL(clicked()), this, SLOT(findFirst()));
	layout->addWidget(findBtn);

	hideBtn = new QPushButton(QIcon("icons/window-close.png"), "");
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn);
	setLayout(layout);
	
	connect(findEdit, SIGNAL(returnPressed()), findBtn, SLOT(click()));
}

TextEditFind::~TextEditFind()
{
	delete findEdit;
	delete findBtn;
	delete hideBtn;
	delete layout;
}

void TextEditFind::show()
{
	findEdit->setFocus(Qt::ShortcutFocusReason);
	QWidget::show();
}

void TextEditFind::findFirst()
{
	if (findEdit->text() == "")
	{
		QMessageBox::information(this, tr("Empty Search Field"),
		"The search field is empty. Please enter a word and click Find.");
	} else {
		bool regex = false;
		bool caseSensitive = false;
		bool wholeWord = false;
		bool wrap = true;
		if (!editor->findFirst(findEdit->text(), regex, caseSensitive, wholeWord, wrap))
		{
			QMessageBox::information(this, tr("Word Not Found"),
			"Sorry, the word cannot be found.");
		}
	}
}


