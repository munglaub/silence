/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub, Yves Adler
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
#include "gui/viewmenu.h"
#include <QMenu>
#include <QAction>


ViewMenu::ViewMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&View"));

	QAction *welcomeView = addAction(tr("Welcome View"));
	connect(welcomeView, SIGNAL(triggered(bool)), this, SLOT(showWelcomeView()));

	addSeparator();

	QAction *showNodeTree = addAction(tr("Node Sidebar"));
	showNodeTree->setCheckable(true);
	// TODO: Controller::create()->getTreeView()->isVisible() does not work
	//	 --> find a working solution which is NOT hardcorded!!
	showNodeTree->setChecked(true);
	connect(showNodeTree, SIGNAL(triggered(bool)), 
		Controller::create()->getTreeView(), SLOT(setVisible(bool)));

	QAction *showInfo = addAction(tr("Information Sidebar"));
	showInfo->setCheckable(true);
	showInfo->setChecked(true);
	connect(showInfo, SIGNAL(triggered(bool)), 
		Controller::create()->getInfoSidebar(), SLOT(setVisible(bool)));

	QAction *showProps = addAction(tr("Node Properties Sidebar"));
	showProps->setCheckable(true);
	showProps->setChecked(false);
	connect(showProps, SIGNAL(triggered(bool)), 
		Controller::create()->getNodePropertyWidget(), SLOT(setVisible(bool)));

	QAction *showNodeSearch = addAction(tr("Search Nodes Sidebar"));
	showNodeSearch->setCheckable(true);
	showNodeSearch->setChecked(true);
	connect(showNodeSearch, SIGNAL(triggered(bool)), 
		Controller::create()->getSearchNodeSidebar(), SLOT(setVisible(bool)));

	addSeparator();

	QAction *linewarp = addAction(tr("Linewarp"));
	linewarp->setCheckable(true);
	linewarp->setEnabled(false);
}


void ViewMenu::showWelcomeView()
{
	// setting contentview to NULL will display welcomeview
	// TODO: find a more elegant solution
	Controller::create()->getContentView()->setContent(0);
}


ViewMenu::~ViewMenu()
{
}

