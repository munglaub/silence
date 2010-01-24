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

#include <kactioncollection.h>
#include <KIcon>
#include <KTextEditor/CommandInterface>
#include <KTextEditor/ConfigInterface>
#include <KTextEditor/Cursor>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KTextEditor/View>
#include <QAction>
#include <QToolBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include "src/controller.h"
#include "src/gui/view/textedit.h"


TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	setupEditor();
	setupActions();

	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(view);
	setLayout(layout);
	
	// cursorposition
	connect(view, SIGNAL(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)), this, SLOT(cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor&)));

	// save
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveContent()));

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

void TextEdit::setupActions()
{
	QAction *tmp;
	actionGroup = new QActionGroup(this);

	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Undo)));
	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Redo)));
	tmp = new QAction(actionGroup);
	tmp->setSeparator(true);
	actionGroup->addAction(tmp);

	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Cut)));
	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Copy)));
	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Paste)));
	tmp = new QAction(actionGroup);
	tmp->setSeparator(true);
	actionGroup->addAction(tmp);

	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::SelectAll)));
	actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Find)));
	tmp = actionGroup->addAction(view->actionCollection()->action(KStandardAction::name(KStandardAction::Replace)));
	tmp->setIcon(KIcon("edit-find-replace"));

	saveAction = view->actionCollection()->action(KStandardAction::name(KStandardAction::Save));
	saveAction->disconnect();

	toolbar = new QToolBar;
	toolbar->addAction(saveAction);
	toolbar->addSeparator();
	EditMenu *menu = Controller::create()->getEditMenu();
	for (int i = 0; i < actionGroup->actions().size(); ++i)
	{
		toolbar->addAction(actionGroup->actions().at(i));
		menu->addAction(actionGroup->actions().at(i));
	}

	QMenu *contextmenu = new QMenu(this);
	for (int i = 0; i < actionGroup->actions().size() - 2; ++i)
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
	Controller::create()->getStatusBar()->setSaveStatus(true);
}

void TextEdit::saveContent()
{
	content->setText(document->text());
	Controller::create()->getStatusBar()->setSaveStatus(true);
}

void TextEdit::setSyntax(QString syntax)
{
	document->setHighlightingMode(syntax);
}

void TextEdit::setVisible(bool visible)
{
	this->QWidget::setVisible(visible);
	Controller::create()->getEditMenu()->setEnabled(true);
	actionGroup->setVisible(visible);
}

void TextEdit::contentChanged()
{
	Controller::create()->getStatusBar()->setSaveStatus(false);
}

void TextEdit::cursorPositionChanged(KTextEditor::View*, const KTextEditor::Cursor &newPosition)
{
	Controller::create()->getStatusBar()->setCursorPosition(newPosition.line() + 1, newPosition.column());
}




