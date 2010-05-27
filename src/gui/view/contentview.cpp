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

#include "src/controller.h"
#include "src/data/node/abstractcontentchange.h"
#include "src/gui/view/contentview.h"
#include "src/gui/view/welcomeview.h"
#include "src/gui/widget/notificationbox.h"


ContentView::ContentView(QWidget *parent)
	: QWidget(parent)
{
	node = 0;
	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	widget = Controller::create()->getWelcomeView();
	layout->addWidget(widget);
	setNode(0);
	setLayout(layout);
}

ContentView::~ContentView()
{
	layout->removeWidget(widget);
	widget->setParent(0);
	delete layout;
}

void ContentView::setNode(Node *node)
{
	if (widget->hasChanged())
	{
		AbstractContentChange *change = widget->getChange();
		if (change)
		{
			QLayout *notification = new NotificationBox(this->node, change);
			layout->insertLayout(0, notification);
		}
	}
	layout->removeWidget(widget);
	widget->setParent(0);
	widget->setVisible(false);
	this->node = node;
	if (!node || !node->getContent()){
		Controller *controller = Controller::create();
		widget = controller->getWelcomeView();
		if (controller->getInfoSidebar())
			controller->getInfoSidebar()->clearInfos();
	} else {
		widget = node->getContent()->getWidget();
	}
	layout->addWidget(widget);
	widget->setVisible(true);
}

