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

#include "controller.h"

Controller* Controller::controller = 0;

Controller::Controller()
{
	contentview = 0;
	infosidebar = 0;
	treeview = 0;
	datastore = 0;
	statusbar = 0;
	nodepropertywidget = 0;
	editmenu = 0;
}

Controller::~Controller()
{
}

Controller* Controller::create()
{
	if (controller == 0)
		controller = new Controller;
	return controller;
}

void Controller::setContentView(ContentView* contentview)
{
	this->contentview = contentview;
}

ContentView* Controller::getContentView() const
{
	return contentview;
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

DataStore* Controller::getDataStore()
{
	if (datastore == 0)
		datastore = new DataStore;
	return datastore;
}

void Controller::setEditMenu(EditMenu *editmenu)
{
	this->editmenu = editmenu;
}

EditMenu* Controller::getEditMenu() const
{
	return editmenu;
}

void Controller::setNodePropertyWidget(NodePropertyWidget *nodepropertywidget)
{
	this->nodepropertywidget = nodepropertywidget;
}

NodePropertyWidget* Controller::getNodePropertyWidget() const
{
	return nodepropertywidget;
}

void Controller::setStatusBar(StatusBar *statusbar)
{
	this->statusbar = statusbar;
}

StatusBar* Controller::getStatusBar() const
{
	return statusbar;
}

