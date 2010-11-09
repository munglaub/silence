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

#include "src/gui/actionmanager.h"
#include <klocalizedstring.h>


ActionManager::ActionManager(KActionCollection *actioncollection)
{
	this->actioncollection = actioncollection;
	createGlobalActions();
}

ActionManager::~ActionManager()
{
	// TODO: implement
}

void ActionManager::createGlobalActions()
{
	addGlobalAction("showlabelmanagement", i18n("Manage Labels"));
	addGlobalAction("shownodemanagement", i18n("Manage Nodetypes"));
	addGlobalAction("showtreenodesidebar", i18n("Node Sidebar"), true);
	addGlobalAction("showinfosidebar", i18n("Information Sidebar"), true);
	addGlobalAction("shownavisidebar", i18n("Navigation Sidebar"), true);
	addGlobalAction("showpropertysidebar", i18n("Node Properties Sidebar"), true);
	addGlobalAction("showsearchsidebar", i18n("Search Nodes Sidebar"), true);

	globalActions["exit"] = actioncollection->addAction(KStandardAction::Quit, "exit");

	KAction *action = addGlobalAction("go-previous", i18nc("go to the previous selected node", "Back"));
	action->setIcon(KIcon("go-previous"));
	action->setShortcut(QKeySequence::Back);

	action = addGlobalAction("go-next", i18nc("go to the next node", "Forward"));
	action->setIcon(KIcon("go-next"));
	action->setShortcut(QKeySequence::Forward);

	action = addGlobalAction("addnode", i18n("Add Node"));
	action->setIcon(KIcon("list-add"));
	action = addGlobalAction("addsubnode", i18n("Add Subnode"));
	action->setIcon(KIcon("view-right-new"));
	action = addGlobalAction("removenode", i18n("Remove Node"));
	action->setIcon(KIcon("list-remove"));
	action = addGlobalAction("shownodeproperties", i18n("Properties"));
	action->setIcon(KIcon("document-properties"));
	action = addGlobalAction("showwelcomeview", i18n("Welcome View"));
	action->setIcon(KIcon("silence"));
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




