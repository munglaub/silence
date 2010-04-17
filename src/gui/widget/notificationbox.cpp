/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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
#include "src/gui/widget/notificationbox.h"


NotificationBox::NotificationBox(Node *node, AbstractContentChange *change)
{
	this->node = node;
	this->change = change;
	setAlignment(Qt::AlignLeft);
	info = new QLabel(tr("You didn't save: ") + "<a href=\"silence://0.0.0.0/" + node->getId().getId() + "\">" + node->getCaption() + "</a>");
	addWidget(info);
	btnSave = new QPushButton(tr("Save"));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));
	addWidget(btnSave);
	btnCancel = new QPushButton(tr("Cancel"));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	addWidget(btnCancel);

	connect(info, SIGNAL(linkActivated(const QString&)), this, SLOT(selectNode()));
	connect(Controller::create()->getTreeView(), SIGNAL(nodeSelected(Node*)), this, SLOT(checkSelection(Node*)));
}

NotificationBox::~NotificationBox()
{
	delete info;
	delete btnSave;
	delete btnCancel;
}

void NotificationBox::save()
{
	change->updateContent();
	exit();
}

void NotificationBox::cancel()
{
	exit();
}

void NotificationBox::selectNode()
{
	Controller::create()->getTreeView()->selectItem(node->getId());
}

void NotificationBox::checkSelection(Node *node)
{
	if (this->node == node)
	{
		change->updateContentView();
		exit();
	}
}

void NotificationBox::exit()
{
	setParent(0);
	delete this;
}

