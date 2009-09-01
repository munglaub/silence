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

