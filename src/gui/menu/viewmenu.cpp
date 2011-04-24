/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
 * Copyright (C) 2009, 2010 Yves Adler <yves.adler@googlemail.com>
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
#include "src/gui/menu/viewmenu.h"
#include "src/gui/actionmanager.h"
#include "src/constants.h"


ViewMenu::ViewMenu()
{
	ActionManager *ac = Controller::create()->getActionManager();
	connect(ac->getGlobalAction(Actions::SHOW_LABELMANAGEMENT), SIGNAL(triggered()), this, SLOT(showLabelManagementDialog()));

	connect(ac->getGlobalAction(Actions::SHOW_NODEMANAGEMENT), SIGNAL(triggered()), this, SLOT(showNodeTypeManagement()));

	KAction *action = ac->getGlobalAction(Actions::SHOW_TREENODESIDEBAR);
	action->setChecked(true);
	// TODO: Controller::create()->getTreeView()->isVisible() does not work
	//	 --> find a working solution which is NOT hardcorded!!
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNodeTree(bool)));
	connect(Controller::create()->getTreeView(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = ac->getGlobalAction(Actions::SHOW_INFOSIDEBAR);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showInfo(bool)));
	connect(Controller::create()->getInfoSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = ac->getGlobalAction(Actions::SHOW_NAVISIDEBAR);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNavigation(bool)));
	connect(Controller::create()->getNavigationSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = ac->getGlobalAction(Actions::SHOW_PROPERTYSIDEBAR);
	action->setChecked(false);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showProperties(bool)));
	connect(Controller::create()->getNodePropertyWidget(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));

	action = ac->getGlobalAction(Actions::SHOW_SEARCHSIDEBAR);
	action->setChecked(true);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNodeSearch(bool)));
	connect(Controller::create()->getSearchNodeSidebar(), SIGNAL(visibilityChanged(bool)), action, SLOT(setChecked(bool)));
}

void ViewMenu::showLabelManagementDialog()
{
	LabelManagementDialog *dlg = new LabelManagementDialog;
	connect(dlg, SIGNAL(exit(LabelManagementDialog*)), this, SLOT(closeLabelManagementDialog(LabelManagementDialog*)));
	Controller::create()->getMainWindow()->showDialog(dlg);
}

void ViewMenu::closeLabelManagementDialog(LabelManagementDialog *dlg)
{
	Controller::create()->getMainWindow()->removeDialog(dlg);
	delete dlg;
	Controller::create()->getNodePropertyWidget()->updateLabels();
	Controller::create()->getSearchNodeSidebar()->updateLabels();
}

void ViewMenu::showNodeTypeManagement()
{
	Controller::create()->getMainWindow()->showNodeTypeManagement();
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


