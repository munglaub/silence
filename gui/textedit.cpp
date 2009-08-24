#include "gui/textedit.h"
#include <Qsci/qscilexercpp.h>
#include <QToolBar>
#include <QVBoxLayout>


TextEdit* TextEdit::textedit = 0;

TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	// Toolbar
	toolbar = new QToolBar;
	saveAction = toolbar->addAction(QIcon("icons/document-save.png"), tr("Save"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveContent()));
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

TextEdit::~TextEdit()
{
	delete saveAction;
	delete toolbar;
	delete editor;
}

TextEdit* TextEdit::create()
{
	if (textedit == 0)
		textedit = new TextEdit;
	return textedit;
}

void TextEdit::setContent(TextNodeContent *content)
{
	this->content = content;
	editor->setText(content->getText());
}

void TextEdit::saveContent()
{
	content->setText(editor->text());
}

void TextEdit::setSyntax(QString syntax)
{
	// TODO: implement
}

