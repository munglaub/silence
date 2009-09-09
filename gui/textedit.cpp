/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
 *
 * This file is part of Silence.
 *
 * Silence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version GPLv2 only of the License.
 *
 * Silence is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "controller.h"
#include "gui/textedit.h"
#include <QApplication>
#include <QClipboard>
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



TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	setupActions();
	setupEditor();

	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(editor);
	findWidget = new TextFind(this);
	findWidget->hide();
	layout->addWidget(findWidget);
	setLayout(layout);
	
	// find
	connect(actionFind, SIGNAL(triggered()), findWidget, SLOT(show()));
	connect(findWidget->getNextBtn(), SIGNAL(clicked()), this, SLOT(findNext()));
	connect(findWidget->getPrevBtn(), SIGNAL(clicked()), this, SLOT(findPrev()));
	connect(findWidget->getFindEdit(), SIGNAL(textChanged(const QString&)), this, SLOT(findFirst()));
	connect(findWidget->getReplaceBtn(), SIGNAL(clicked()), this, SLOT(replace()));
	connect(findWidget->getReplaceAllBtn(), SIGNAL(clicked()), this, SLOT(replaceAll()));

	// cursorposition
	connect(editor, SIGNAL(cursorPositionChanged(int, int)), Controller::create()->getStatusBar(), SLOT(setCursorPosition(int, int)));

	// save
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveContent()));
	
	// undo, redo
	connect(editor, SIGNAL(textChanged()), this, SLOT(textModified()));

	setWindowModified(editor->isModified());
	actionUndo->setEnabled(editor->isUndoAvailable());
	actionRedo->setEnabled(editor->isRedoAvailable());

	connect(actionUndo, SIGNAL(triggered()), editor, SLOT(undo()));
	connect(actionRedo, SIGNAL(triggered()), editor, SLOT(redo()));

	// cut, copy, paste
	actionCut->setEnabled(false);
	actionCopy->setEnabled(false);

	connect(actionCut, SIGNAL(triggered()), editor, SLOT(cut()));
	connect(actionCopy, SIGNAL(triggered()), editor, SLOT(copy()));
	connect(actionPaste, SIGNAL(triggered()), editor, SLOT(paste()));

	connect(editor, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
	connect(editor, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

	connect(QApplication::clipboard(), SIGNAL(dataChanged()), 
			this, SLOT(clipboardDataChanged()));
}

TextEdit::~TextEdit()
{
	delete actionSave;
	delete actionUndo;
	delete actionRedo;
	delete actionCut;
	delete actionCopy;
	delete actionPaste;
	delete actionFind;
	delete toolbar;
	delete editor;
	delete findWidget;
	delete layout;
}

void TextEdit::setupActions()
{
	EditMenu *menu = Controller::create()->getEditMenu();
	// Toolbar
	toolbar = new QToolBar;
	actionSave = toolbar->addAction(QIcon("icons/document-save.png"), tr("Save"));
	actionSave->setShortcut(QKeySequence::Save);
	toolbar->addSeparator();

	actionUndo = toolbar->addAction(QIcon("icons/edit-undo.png"), tr("Undo"));
	menu->addAction(actionUndo);
	actionUndo->setShortcut(QKeySequence::Undo);
	actionRedo = toolbar->addAction(QIcon("icons/edit-redo.png"), tr("Redo"));
	menu->addAction(actionRedo);
	actionRedo->setShortcut(QKeySequence::Redo);
	actionCut = toolbar->addAction(QIcon("icons/edit-cut.png"), tr("Cut"));
	menu->addAction(actionCut);
	actionCut->setShortcut(QKeySequence::Cut);
	actionCopy = toolbar->addAction(QIcon("icons/edit-copy.png"), tr("Copy"));
	menu->addAction(actionCopy);
	actionCopy->setShortcut(QKeySequence::Copy);
	actionPaste = toolbar->addAction(QIcon("icons/edit-paste.png"), tr("Paste"));
	menu->addAction(actionPaste);
	actionPaste->setShortcut(QKeySequence::Paste);
	toolbar->addSeparator();

	actionFind = toolbar->addAction(QIcon("icons/edit-find.png"), tr("Find"));
	actionFind->setShortcut(QKeySequence::Find);
	toolbar->addAction(QIcon("icons/edit-find-replace.png"), tr("Find/Replace"));
}

void TextEdit::setupEditor()
{
	// Editor
	editor = new QsciScintilla;

	editor->setLexer();
	editor->setTabWidth(4);
	// show linenumbers
	editor->setMarginWidth(0, 35);
	editor->setMarginLineNumbers(0, true);
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
	{
		editor->setLexer();
		QFont font("Monospace", 10);
		editor->setFont(font);
	}
}

void TextEdit::textModified()
{
	actionUndo->setEnabled(editor->isUndoAvailable());
	actionRedo->setEnabled(editor->isRedoAvailable());
}

void TextEdit::clipboardDataChanged()
{
	actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

void TextEdit::setVisible(bool visible)
{
	this->QWidget::setVisible(visible);
	actionUndo->setVisible(visible);
	actionRedo->setVisible(visible);
	actionCut->setVisible(visible);
	actionCopy->setVisible(visible);
	actionPaste->setVisible(visible);
}

void TextEdit::findFirst()
{
	editor->setCursorPosition(0, 0);
	find(true);
}

void TextEdit::findNext()
{
	find(true);
}

void TextEdit::findPrev()
{
	find(false);
}

bool TextEdit::find(bool forward)
{
	bool found = false;
	if (findWidget->getSearchString().isEmpty())
		return found;

	bool regex = false;
	bool caseSensitive = findWidget->getCaseSensitivity();
	bool wholeWord = findWidget->getWholeWord();
	bool wrap = true;
	int line = -1;
	int index = -1;
	if (forward == false)
	{
		editor->getCursorPosition(&line, &index);
		--index;
	}
	bool show = true;
	found = editor->findFirst(findWidget->getSearchString(), regex, caseSensitive, wholeWord, wrap, forward, line, index, show);
	findWidget->setFound(found);

	return found;
}

void TextEdit::replace()
{
	if (editor->selectedText() == findWidget->getSearchString())
		editor->replace(findWidget->getReplaceString());
	else
		if (find(true))
			editor->replace(findWidget->getReplaceString());
}

void TextEdit::replaceAll()
{
	editor->setCursorPosition(0, 0);
	bool found = false;
	do {
		found = find(true);
		if (found)
			editor->replace(findWidget->getReplaceString());
	} while (found);
}


