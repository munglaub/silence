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

#include "src/controller.h"

Controller* Controller::controller = 0;

Controller::Controller()
{
	mainwindow = 0;
	contentview = 0;
	welcomeview = 0;
	textedit = 0;
	richtextedit = 0;
	customcontentview = 0;
	infosidebar = 0;
	treeview = 0;
	datastore = 0;
	statusbar = 0;
	nodepropertywidget = 0;
	navigationsidebar = 0;
	actionmanager = 0;
	changemanager = 0;
}

Controller::~Controller()
{
	delete datastore;

	if (welcomeview)
		delete welcomeview;
	if (textedit)
		delete textedit;
	if (richtextedit)
		delete richtextedit;
	if (customcontentview)
		delete customcontentview;
	if (changemanager)
		delete changemanager;
}

Controller* Controller::create()
{
	if (controller == 0)
		controller = new Controller;
	return controller;
}

void Controller::setMainWindow(MainWindow* mainwindow)
{
	this->mainwindow = mainwindow;
}

MainWindow* Controller::getMainWindow()
{
	return mainwindow;
}

void Controller::setContentView(ContentView* contentview)
{
	this->contentview = contentview;
}

ContentView* Controller::getContentView() const
{
	return contentview;
}

WelcomeView* Controller::getWelcomeView()
{
	if (welcomeview == 0)
		welcomeview = new WelcomeView;
	return welcomeview;
}

TextEdit* Controller::getTextEdit()
{
	if (textedit == 0)
		textedit = new TextEdit();
	return textedit;
}

RichTextEdit* Controller::getRichTextEdit()
{
	if (richtextedit == 0)
		richtextedit = new RichTextEdit();
	return richtextedit;
}

CustomContentView* Controller::getCustomContentView()
{
	if (customcontentview == 0)
		customcontentview = new CustomContentView;
	return customcontentview;
}

void Controller::setActionManager(ActionManager *actionmanager)
{
	this->actionmanager = actionmanager;
}

ActionManager* Controller::getActionManager() const
{
	return actionmanager;
}

ChangeManager* Controller::getChangeManager()
{
	if (changemanager == 0)
		changemanager = new ChangeManager;
	return changemanager;
}

void Controller::setInfoSidebar(InfoSidebar* infosidebar)
{
	this->infosidebar = infosidebar;
}

InfoSidebar* Controller::getInfoSidebar() const
{
	return infosidebar;
}

void Controller::setSearchNodeSidebar(SearchNodeSidebar* searchsidebar)
{
	this->searchsidebar = searchsidebar;
}

SearchNodeSidebar* Controller::getSearchNodeSidebar() const
{
	return searchsidebar;
}

void Controller::setTreeView(TreeView* treeview)
{
	this->treeview = treeview;
}

TreeView* Controller::getTreeView() const
{
	return treeview;
}

AbstractDataStore* Controller::getDataStore()
{
	if (datastore == 0)
		datastore = new XmlDataStore;
	return datastore;
}

void Controller::setNodePropertyWidget(NodePropertyWidget *nodepropertywidget)
{
	this->nodepropertywidget = nodepropertywidget;
}

NodePropertyWidget* Controller::getNodePropertyWidget() const
{
	return nodepropertywidget;
}

void Controller::setNavigationSidebar(NavigationSidebar *navigationsidebar)
{
	this->navigationsidebar = navigationsidebar;
}

NavigationSidebar* Controller::getNavigationSidebar() const
{
	return navigationsidebar;
}

void Controller::setStatusBar(SiStatusBar *statusbar)
{
	this->statusbar = statusbar;
}

SiStatusBar* Controller::getStatusBar() const
{
	return statusbar;
}

