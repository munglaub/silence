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
#include "gui/view/contentview.h"
#include "gui/view/welcomeview.h"


ContentView::ContentView(QWidget *parent)
	: QWidget(parent)
{
	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	widget = Controller::create()->getWelcomeView();
	layout->addWidget(widget);
	setContent(NULL);
	setLayout(layout);
}

ContentView::~ContentView()
{
	delete layout;
}

void ContentView::setContent(AbstractNodeContent *content)
{
	layout->removeWidget(widget);
	widget->setVisible(false);
	if (!content){
		Controller *controller = Controller::create();
		widget = controller->getWelcomeView();
		if (controller->getInfoSidebar())
			controller->getInfoSidebar()->clearInfos();
		if (controller->getEditMenu())
			controller->getEditMenu()->setEnabled(false);
	} else {
		widget = content->getWidget();
	}
	layout->addWidget(widget);
	widget->setVisible(true);
}

