#include "textedit.h"
#include <Qsci/qscilexercpp.h>
#include <QVBoxLayout>
#include <QToolBar>


TextEdit* TextEdit::textedit = 0;

TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	// Toolbar
	QToolBar *toolbar = new QToolBar;
	toolbar->addAction(tr("save"));
	toolbar->addSeparator();
	toolbar->addAction(tr("copy"));
	toolbar->addAction(tr("cut"));
	toolbar->addAction(tr("paste"));
	toolbar->addSeparator();
	toolbar->addAction(tr("undo"));
	toolbar->addAction(tr("redo"));
	toolbar->addSeparator();
	toolbar->addAction(tr("find"));
	toolbar->addAction(tr("replace"));

	editor = new QsciScintilla;

	// temporarily with a c++ lexer
	editor->setLexer(new QsciLexerCPP());
	// show linenumbers
	editor->setMarginWidth(0, 35);
	editor->setMarginLineNumbers(0, true);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(editor);
	setLayout(layout);
}

TextEdit* TextEdit::create()
{
	if (textedit == 0)
		textedit = new TextEdit;
	return textedit;
}

void TextEdit::setText(const QString &text)
{
	editor->setText(text);
}


TextEdit::~TextEdit()
{
	delete editor;
}


