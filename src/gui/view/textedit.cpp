/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <KIcon>
#include <KTextEditor/CommandInterface>
#include <KTextEditor/ConfigInterface>
#include <KTextEditor/Cursor>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KTextEditor/View>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include "src/constants.h"
#include "src/controller.h"
#include "src/data/node/textcontentchange.h"
#include "src/gui/view/textedit.h"


TextEdit::TextEdit()
{
	setupEditor();
	setupActions();
	isChanged = false;

	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(view);
	setLayout(layout);
	
	connect(view, SIGNAL(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)), this, SLOT(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)));
	connect(document, SIGNAL(textChanged(KTextEditor::Document*)), this, SLOT(contentChanged()));
}

TextEdit::~TextEdit()
{
	delete view;
	delete document;
	delete editor;
	delete actionGroup;
	delete toolbar;
	delete layout;
}

void TextEdit::addAction(QAction **keAction, QAction **action, KStandardAction::StandardAction kename, QString name){
	*keAction = view->actionCollection()->action(KStandardAction::name(kename));
	(*keAction)->setShortcut(QKeySequence());
	*action = Controller::create()->getActionManager()->getAction(name);
	actionGroup->addAction(*action);
}

void TextEdit::updateActions(){
	undoAction->setEnabled(keundoAction->isEnabled());
	redoAction->setEnabled(keredoAction->isEnabled());
	cutAction->setEnabled(kecutAction->isEnabled());
	copyAction->setEnabled(kecopyAction->isEnabled());
	pasteAction->setEnabled(kepasteAction->isEnabled());
}

void TextEdit::setupActions()
{
	QAction *action;
	actionGroup = new QActionGroup(this);

	view->actionCollection()->removeAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Save)));
	saveAction = Controller::create()->getActionManager()->getAction(Actions::SAVE);
	actionGroup->addAction(saveAction);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveContent()));

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);

	addAction(&keundoAction, &undoAction, KStandardAction::Undo, Actions::UNDO);
	connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

	addAction(&keredoAction, &redoAction, KStandardAction::Redo, Actions::REDO);
	connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);


	addAction(&kecutAction, &cutAction, KStandardAction::Cut, Actions::CUT);
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
	addAction(&kecopyAction, &copyAction, KStandardAction::Copy, Actions::COPY);
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
	addAction(&kepasteAction, &pasteAction, KStandardAction::Paste, Actions::PASTE);
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);


	addAction(&keselectallAction, &selectallAction, KStandardAction::SelectAll, Actions::SELECTALL);
	connect(selectallAction, SIGNAL(triggered()), this, SLOT(selectall()));
	addAction(&kefindAction, &findAction, KStandardAction::Find, Actions::FIND);
	connect(findAction, SIGNAL(triggered()), this, SLOT(find()));
	addAction(&kereplaceAction, &replaceAction, KStandardAction::Replace, Actions::REPLACE);
	connect(replaceAction, SIGNAL(triggered()), this, SLOT(replace()));

	toolbar = new QToolBar;
	for (int i = 0; i < actionGroup->actions().size(); ++i)
	{
		toolbar->addAction(actionGroup->actions().at(i));
	}

	QMenu *contextmenu = new QMenu(this);
	for (int i = 2; i < actionGroup->actions().size() - 2; ++i)
		contextmenu->addAction(actionGroup->actions().at(i));
	view->setContextMenu(contextmenu);
}

void TextEdit::setupEditor()
{
	editor = KTextEditor::EditorChooser::editor();
	document = editor->createDocument(0);
	document->setHighlightingMode("None");
	view = qobject_cast<KTextEditor::View*>(document->createView(this));

	KTextEditor::ConfigInterface *interface = qobject_cast<KTextEditor::ConfigInterface*>(view);
	interface->setConfigValue("line-numbers", true);
	interface->setConfigValue("dynamic-word-wrap", true);

	KTextEditor::CommandInterface *iface = qobject_cast<KTextEditor::CommandInterface*>(editor);
	if (iface)
	{
		KTextEditor::Command *cmd = iface->queryCommand("set-tab-width");
		if (cmd){
			QString msg;
			cmd->exec(view, "set-tab-width 4", msg);
		}
		cmd = iface->queryCommand("set-indent-width");
		if (cmd){
			QString msg;
			cmd->exec(view, "set-indent-width 4", msg);
		}
	}
}

void TextEdit::setContent(TextNodeContent *content)
{
	this->content = content;
	document->clear();
	document->setText(content->getText());
	view->setCursorPosition(KTextEditor::Cursor(0, 0));
	Controller::create()->getStatusBar()->setSaveStatus(true);
	isChanged = false;
}

void TextEdit::setText(QString text)
{
	document->clear();
	document->setText(text);
	view->setCursorPosition(KTextEditor::Cursor(0, 0));
}

void TextEdit::saveContent()
{
	if (isActive){
		content->setText(document->text());
		Controller::create()->getStatusBar()->setSaveStatus(true);
		isChanged = false;
	}
}

void TextEdit::setSyntax(QString syntax)
{
	document->setHighlightingMode(syntax);
}

bool TextEdit::hasChanged()
{
	return isChanged;
}

AbstractContentChange* TextEdit::getChange()
{
	return new TextContentChange(document->text(), content, this);
}

void TextEdit::setVisible(bool visible)
{
	this->isActive = visible;
	this->QWidget::setVisible(visible);
	for (int i = 0; i < actionGroup->actions().size(); ++i)
		actionGroup->actions().at(i)->setVisible(visible);
	updateActions();
}

void TextEdit::contentChanged()
{
	Controller::create()->getStatusBar()->setSaveStatus(false);
	isChanged = true;
}

void TextEdit::cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor &newPosition)
{
	Controller::create()->getStatusBar()->setCursorPosition(newPosition.line() + 1, newPosition.column());
	updateActions();
}

void TextEdit::execute(QAction *action){
	if (isActive){
		action->trigger();
		updateActions();
	}
}

void TextEdit::undo(){
	execute(keundoAction);
}

void TextEdit::redo(){
	execute(keredoAction);
}

void TextEdit::cut(){
	execute(kecutAction);
}

void TextEdit::copy(){
	execute(kecopyAction);
}

void TextEdit::paste(){
	execute(kepasteAction);
}

void TextEdit::selectall(){
	execute(keselectallAction);
}

void TextEdit::find(){
	execute(kefindAction);
}

void TextEdit::replace(){
	execute(kereplaceAction);
}




