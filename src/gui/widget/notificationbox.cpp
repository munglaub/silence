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

#include <klocalizedstring.h>
#include <QToolTip>
#include "src/controller.h"
#include "src/gui/widget/notificationbox.h"


NotificationBox::NotificationBox(Node *node, AbstractContentChange *change)
{
	boxlayout = new QHBoxLayout;

	this->node = node;
	this->change = change;
	info = new QLabel(i18n("You didn't save:") + " <a href=\"silence://0.0.0.0/" + node->getId().getId() + "\">" + node->getCaption() + "</a>");
	boxlayout->addWidget(info);
	boxlayout->addStretch();
	btnSave = new QPushButton(i18n("Save"));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));
	boxlayout->addWidget(btnSave);
	btnCancel = new QPushButton(i18n("Cancel"));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	boxlayout->addWidget(btnCancel);

	connect(info, SIGNAL(linkActivated(const QString&)), this, SLOT(selectNode()));
	connect(Controller::create()->getTreeView(), SIGNAL(nodeSelected(Node*)), this, SLOT(checkSelection(Node*)));

	box = new QWidget;
	QString css = QString("QWidget { background: %1 } QPushButton { background: %2 }")
					.arg(QToolTip::palette().toolTipBase().color().name())
					.arg(QToolTip::palette().window().color().name());
	box->setStyleSheet(css);
	box->setLayout(boxlayout);
	addWidget(box);
}

NotificationBox::~NotificationBox()
{
	delete info;
	delete btnSave;
	delete btnCancel;
	delete boxlayout;
	delete box;
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

