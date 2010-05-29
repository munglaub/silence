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
#include "src/controller.h"
#include "src/data/node/textcontentchange.h"
#include "src/gui/view/textedit.h"


TextEdit::TextEdit(KActionCollection *actionCollection)
{
	setupEditor();
	setupActions(actionCollection);
	isChanged = false;

	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(view);
	setLayout(layout);
	
	// cursorposition
	connect(view, SIGNAL(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)), this, SLOT(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)));

	// modificationstatus
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

void TextEdit::addAction(KActionCollection *actionCollection, KStandardAction::StandardAction actionType, QString name)
{
	QAction *action = view->actionCollection()->action(KStandardAction::name(actionType));
	actionCollection->addAction(name, action);
	actionGroup->addAction(action);
}

void TextEdit::setupActions(KActionCollection *actionCollection)
{
	QAction *action;
	actionGroup = new QActionGroup(this);

	addAction(actionCollection, KStandardAction::Save, "te_save");
	saveAction = actionCollection->action("te_save");
	saveAction->disconnect();
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveContent()));

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);

	addAction(actionCollection, KStandardAction::Undo, "te_undo");
	addAction(actionCollection, KStandardAction::Redo, "te_redo");

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);

	addAction(actionCollection, KStandardAction::Cut, "te_cut");
	addAction(actionCollection, KStandardAction::Copy, "te_copy");
	addAction(actionCollection, KStandardAction::Paste, "te_paste");

	action = new QAction(actionGroup);
	action->setSeparator(true);
	actionGroup->addAction(action);

	addAction(actionCollection, KStandardAction::SelectAll, "te_selectall");
	addAction(actionCollection, KStandardAction::Find, "te_find");
	addAction(actionCollection, KStandardAction::Replace, "te_replace");
	actionCollection->action("te_replace")->setIcon(KIcon("edit-find-replace"));

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
	content->setText(document->text());
	Controller::create()->getStatusBar()->setSaveStatus(true);
	isChanged = false;
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
	this->QWidget::setVisible(visible);
	actionGroup->setVisible(visible);
}

void TextEdit::contentChanged()
{
	Controller::create()->getStatusBar()->setSaveStatus(false);
	isChanged = true;
}

void TextEdit::cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor &newPosition)
{
	Controller::create()->getStatusBar()->setCursorPosition(newPosition.line() + 1, newPosition.column());
}




