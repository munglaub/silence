#include "gui/textedit.h"
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qscilexercss.h>
#include <Qsci/qscilexerd.h>
#include <Qsci/qscilexerdiff.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexeridl.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerpov.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerruby.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qscilexervhdl.h>
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
	toolbar->addAction(tr("select all"));
	toolbar->addSeparator();
	toolbar->addAction(tr("undo"));
	toolbar->addAction(tr("redo"));
	toolbar->addSeparator();
	toolbar->addAction(tr("find"));
	toolbar->addAction(tr("replace"));

	editor = new QsciScintilla;

	// temporarily with a c++ lexer
	editor->setLexer();
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
	if (syntax == "Bash")
		editor->setLexer(new QsciLexerBash(editor));
	else if (syntax == "Batch")
		editor->setLexer(new QsciLexerBatch(editor));
	else if (syntax == "CMake")
		editor->setLexer(new QsciLexerCMake(editor));
	else if (syntax == "C++")
		editor->setLexer(new QsciLexerCPP(editor));
	else if (syntax == "C#")
		editor->setLexer(new QsciLexerCSharp(editor));
	else if (syntax == "CSS")
		editor->setLexer(new QsciLexerCSS(editor));
	else if (syntax == "D")
		editor->setLexer(new QsciLexerD(editor));
	else if (syntax == "Diff")
		editor->setLexer(new QsciLexerDiff(editor));
	else if (syntax == "HTML")
		editor->setLexer(new QsciLexerHTML(editor));
	else if (syntax == "IDL")
		editor->setLexer(new QsciLexerIDL(editor));
	else if (syntax == "Java")
		editor->setLexer(new QsciLexerJava(editor));
	else if (syntax == "JavaScript")
		editor->setLexer(new QsciLexerJavaScript(editor));
	else if (syntax == "Lua")
		editor->setLexer(new QsciLexerLua(editor));
	else if (syntax == "Makefile")
		editor->setLexer(new QsciLexerMakefile(editor));
	else if (syntax == "Perl")
		editor->setLexer(new QsciLexerPerl(editor));
	else if (syntax == "POV")
		editor->setLexer(new QsciLexerPOV(editor));
	else if (syntax == "Python")
		editor->setLexer(new QsciLexerPython(editor));
	else if (syntax == "Ruby")
		editor->setLexer(new QsciLexerRuby(editor));
	else if (syntax == "SQL")
		editor->setLexer(new QsciLexerSQL(editor));
	else if (syntax == "TeX")
		editor->setLexer(new QsciLexerTeX(editor));
	else if (syntax == "VHDL")
		editor->setLexer(new QsciLexerVHDL(editor));
	else
		editor->setLexer();
}

