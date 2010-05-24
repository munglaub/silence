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

#include <kaction.h>
#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/gui/dialog/labelmanagementdialog.h"
#include "src/gui/menu/viewmenu.h"


ViewMenu::ViewMenu(KActionCollection *actionCollection)
{
	KAction *action = actionCollection->addAction("showwelcomeview");
	action->setText(i18n("Welcome View"));
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showWelcomeView()));

	action = actionCollection->addAction("showlabelmanagement");
	action->setText(i18n("Manage Labels"));
	connect(action, SIGNAL(triggered()), this, SLOT(showLabelManagementDialog()));

	action = actionCollection->addAction("showtreenodesidebar");
	action->setText(i18n("Node Sidebar"));
	action->setCheckable(true);
	// TODO: Controller::create()->getTreeView()->isVisible() does not work
	//	 --> find a working solution which is NOT hardcorded!!
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNodeTree(bool)));
	connect(Controller::create()->getTreeView(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = actionCollection->addAction("showinfosidebar");
	action->setText(i18n("Information Sidebar"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showInfo(bool)));
	connect(Controller::create()->getInfoSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = actionCollection->addAction("shownavisidebar");
	action->setText(i18n("Navigation Sidebar"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNavigation(bool)));
	connect(Controller::create()->getNavigationSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = actionCollection->addAction("showpropertysidebar");
	action->setText(i18n("Node Properties Sidebar"));
	action->setCheckable(true);
	action->setChecked(false);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showProperties(bool)));
	connect(Controller::create()->getNodePropertyWidget(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = actionCollection->addAction("showsearchsidebar");
	action->setText(i18n("Search Nodes Sidebar"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNodeSearch(bool)));
	connect(Controller::create()->getSearchNodeSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));
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


