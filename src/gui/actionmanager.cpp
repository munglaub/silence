/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#include <klocalizedstring.h>
#include "src/constants.h"
#include "src/gui/actionmanager.h"


ActionManager::ActionManager(KActionCollection *actioncollection)
{
	this->actioncollection = actioncollection;
	createGlobalActions();
	createActions();
}

ActionManager::~ActionManager()
{
	// TODO: implement
}

void ActionManager::createGlobalActions()
{
	addGlobalAction(Actions::SHOW_LABELMANAGEMENT, i18n("Manage Labels"));
	addGlobalAction(Actions::SHOW_NODEMANAGEMENT, i18n("Manage Nodetypes"));
	addGlobalAction(Actions::SHOW_TREENODESIDEBAR, i18n("Node Sidebar"), true);
	addGlobalAction(Actions::SHOW_INFOSIDEBAR, i18n("Information Sidebar"), true);
	addGlobalAction(Actions::SHOW_NAVISIDEBAR, i18n("Navigation Sidebar"), true);
	addGlobalAction(Actions::SHOW_PROPERTYSIDEBAR, i18n("Node Properties Sidebar"), true);
	addGlobalAction(Actions::SHOW_SEARCHSIDEBAR, i18n("Search Nodes Sidebar"), true);

	globalActions[Actions::EXIT] = actioncollection->addAction(KStandardAction::Quit, "exit");

	KAction *action = addGlobalAction(Actions::GO_PREVIOUS, i18nc("go to the previous selected node", "Back"));
	action->setIcon(KIcon("go-previous"));
	action->setShortcut(QKeySequence::Back);

	action = addGlobalAction(Actions::GO_NEXT, i18nc("go to the next node", "Forward"));
	action->setIcon(KIcon("go-next"));
	action->setShortcut(QKeySequence::Forward);

	action = addGlobalAction(Actions::ADD_NODE, i18n("Add Node"));
	action->setIcon(KIcon("list-add"));
	action = addGlobalAction(Actions::ADD_SUBNODE, i18n("Add Subnode"));
	action->setIcon(KIcon("view-right-new"));
	action = addGlobalAction(Actions::REMOVE_NODE, i18n("Remove Node"));
	action->setIcon(KIcon("list-remove"));
	action = addGlobalAction(Actions::SHOW_NODE_PROPERTIES, i18n("Properties"));
	action->setIcon(KIcon("document-properties"));
	action = addGlobalAction(Actions::SHOW_WELCOMEVIEW, i18n("Welcome View"));
	action->setIcon(KIcon("silence"));
}

void ActionManager::createActions()
{
	addAction(KStandardAction::Save, Actions::SAVE);
	addAction(KStandardAction::Undo, Actions::UNDO);
	addAction(KStandardAction::Redo, Actions::REDO);
	addAction(KStandardAction::Cut, Actions::CUT);
	addAction(KStandardAction::Copy, Actions::COPY);
	addAction(KStandardAction::Paste, Actions::PASTE);
	addAction(KStandardAction::SelectAll, Actions::SELECTALL);

	addAction(Actions::BOLD, i18nc("toggle selected text to bold", "Bold"), KIcon("format-text-bold"), true);
	actions[Actions::BOLD]->setShortcut(Qt::CTRL + Qt::Key_B);
	QFont bold;
	bold.setBold(true);
	actions[Actions::BOLD]->setFont(bold);

	addAction(Actions::ITALIC, i18nc("toggle selected text to italic", "Italic"), KIcon("format-text-italic"), true);
	actions[Actions::ITALIC]->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont italic;
	italic.setItalic(true);
	actions[Actions::ITALIC]->setFont(italic);

	addAction(Actions::UNDERLINE, i18nc("underline selected text", "Underline"), KIcon("format-text-underline"), true);
	actions[Actions::UNDERLINE]->setShortcut(Qt::CTRL + Qt::Key_U);
	QFont underline;
	underline.setUnderline(true);
	actions[Actions::UNDERLINE]->setFont(underline);

	addAction(Actions::ALIGN_LEFT, i18nc("justify text left", "Left"), KIcon("format-justify-left"), true);
	addAction(Actions::ALIGN_RIGHT, i18nc("justify text right", "Right"), KIcon("format-justify-right"), true);
	addAction(Actions::ALIGN_CENTER, i18nc("justify text centered", "Center"), KIcon("format-justify-center"), true);
	addAction(Actions::ALIGN_JUSTIFY, i18n("Justify"), KIcon("format-justify-fill"), true);

	addAction(Actions::UNORDERED_LIST, i18n("Create Unordered List"), KIcon("format-list-unordered"));
	addAction(Actions::ORDERED_LIST, i18n("Create Ordered List"), KIcon("format-list-ordered"));
	addAction(Actions::INDENT_MORE, i18n("Indent more"), KIcon("format-indent-more"));
	addAction(Actions::INDENT_LESS, i18n("Indent less"), KIcon("format-indent-less"));

	addAction(Actions::INSERT_IMAGE, i18n("Insert Image"), KIcon("insert-image"));
	addAction(Actions::INSERT_RULE, i18n("Insert Horizontal Rule"), KIcon("insert-horizontal-rule"));
	addAction(Actions::INSERT_LINK, i18n("Insert Link"), KIcon("insert-link"));
	addAction(Actions::INSERT_TABLE, i18n("Insert Table"), KIcon("insert-table"));

	addAction(Actions::FIND, i18n("&Find"), KIcon("edit-find"));
	actions[Actions::FIND]->setShortcut(QKeySequence::Find);
	addAction(Actions::REPLACE, i18n("Find/Replace"), KIcon("edit-find-replace"));
	addAction(Actions::TEXT_COLOR, i18n("Text Color"), KIcon("format-text-color"));
	addAction(Actions::TEXT_BGCOLOR, i18n("Text Highlight"), KIcon("format-fill-color"));

	addAction(Actions::INSERT_TABLE_ROW, i18n("Insert Table Row"), QIcon(":/icons/actions/insert-table-row.png"));
	addAction(Actions::INSERT_TABLE_COLUMN, i18n("Insert Table Column"), QIcon(":/icons/actions/insert-table-column.png"));
	addAction(Actions::REMOVE_TABLE_ROW, i18n("Remove Table Row"), QIcon(":/icons/actions/remove-table-row.png"));
	addAction(Actions::REMOVE_TABLE_COLUMN, i18n("Remove Table Column"), QIcon(":/icons/actions/remove-table-column.png"));
}

KAction* ActionManager::addAction(KStandardAction::StandardAction actionType, QString name)
{
	actions[name] = actioncollection->addAction(actionType, name);
	return actions[name];
}

KAction* ActionManager::addAction(QString name, QString text, QIcon icon, bool checkable){
	actions[name] = actioncollection->addAction(name);
	actions[name]->setText(text);
	actions[name]->setIcon(icon);
	actions[name]->setCheckable(checkable);
	return actions[name];
}

KAction* ActionManager::addGlobalAction(QString name, QString text, bool checkable)
{
	globalActions[name] = actioncollection->addAction(name);
	globalActions[name]->setText(text);
	globalActions[name]->setCheckable(checkable);
	return globalActions[name];
}

KAction* ActionManager::getAction(QString name)
{
	return actions[name];
}

KAction* ActionManager::getGlobalAction(QString name)
{
	return globalActions[name];
}




