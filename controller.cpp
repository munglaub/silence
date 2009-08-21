#include "controller.h"

Controller* Controller::controller = 0;

Controller::Controller()
{
	contentview = 0;
	infosidebar = 0;
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

