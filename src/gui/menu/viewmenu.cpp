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

#include <QAction>
#include <QMenu>
#include "src/controller.h"
#include "src/gui/dialog/labelmanagementdialog.h"
#include "src/gui/menu/viewmenu.h"


ViewMenu::ViewMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&View"));

	welcomeViewAction = addAction(tr("Welcome View"));
	connect(welcomeViewAction, SIGNAL(triggered(bool)), this, SLOT(showWelcomeView()));

	showLabelManagementAction = addAction(tr("Manage Labels"));
	connect(showLabelManagementAction, SIGNAL(triggered()), this, SLOT(showLabelManagementDialog()));

	addSeparator();

	showNodeTreeAction = addAction(tr("Node Sidebar"));
	showNodeTreeAction->setCheckable(true);
	// TODO: Controller::create()->getTreeView()->isVisible() does not work
	//	 --> find a working solution which is NOT hardcorded!!
	showNodeTreeAction->setChecked(true);
	connect(showNodeTreeAction, SIGNAL(triggered(bool)), this, SLOT(showNodeTree(bool)));
	connect(Controller::create()->getTreeView(), SIGNAL(visibilityChanged(bool)), showNodeTreeAction, SLOT(setChecked(bool)));

	showInfoAction = addAction(tr("Information Sidebar"));
	showInfoAction->setCheckable(true);
	showInfoAction->setChecked(true);
	connect(showInfoAction, SIGNAL(triggered(bool)), this, SLOT(showInfo(bool)));
	connect(Controller::create()->getInfoSidebar(), SIGNAL(visibilityChanged(bool)), showInfoAction, SLOT(setChecked(bool)));

	showNavigationAction = addAction(tr("Navigation Sidebar"));
	showNavigationAction->setCheckable(true);
	showNavigationAction->setChecked(true);
	connect(showNavigationAction, SIGNAL(triggered(bool)), this, SLOT(showNavigation(bool)));
	connect(Controller::create()->getNavigationSidebar(), SIGNAL(visibilityChanged(bool)), showNavigationAction, SLOT(setChecked(bool)));

	showPropertiesAction = addAction(tr("Node Properties Sidebar"));
	showPropertiesAction->setCheckable(true);
	showPropertiesAction->setChecked(false);
	connect(showPropertiesAction, SIGNAL(triggered(bool)), this, SLOT(showProperties(bool)));
	connect(Controller::create()->getNodePropertyWidget(), SIGNAL(visibilityChanged(bool)), showPropertiesAction, SLOT(setChecked(bool)));

	showNodeSearchAction = addAction(tr("Search Nodes Sidebar"));
	showNodeSearchAction->setCheckable(true);
	showNodeSearchAction->setChecked(true);
	connect(showNodeSearchAction, SIGNAL(triggered(bool)), this, SLOT(showNodeSearch(bool)));
	connect(Controller::create()->getSearchNodeSidebar(), SIGNAL(visibilityChanged(bool)), showNodeSearchAction, SLOT(setChecked(bool)));
}

ViewMenu::~ViewMenu()
{
	delete welcomeViewAction;
	delete showNodeTreeAction;
	delete showInfoAction;
	delete showPropertiesAction;
	delete showNodeSearchAction;
	delete showLabelManagementAction;
}

void ViewMenu::showWelcomeView()
{
	// setting contentview to NULL will display welcomeview
	// TODO: find a more elegant solution
	Controller::create()->getContentView()->setNode(0);
}

void ViewMenu::showLabelManagementDialog()
{
	LabelManagementDialog *dlg = new LabelManagementDialog;
	dlg->exec();
	delete dlg;
	Controller::create()->getNodePropertyWidget()->updateLabels();
	Controller::create()->getSearchNodeSidebar()->updateLabels();
}

void ViewMenu::showNodeTree(bool visible)
{
	Controller::create()->getTreeView()->setVisible(visible);
}

void ViewMenu::showInfo(bool visible)
{
	Controller::create()->getInfoSidebar()->setVisible(visible);
}

void ViewMenu::showNavigation(bool visible)
{
	Controller::create()->getNavigationSidebar()->setVisible(visible);
}

void ViewMenu::showProperties(bool visible)
{
	Controller::create()->getNodePropertyWidget()->setVisible(visible);
}

void ViewMenu::showNodeSearch(bool visible)
{
	Controller::create()->getSearchNodeSidebar()->setVisible(visible);
}


