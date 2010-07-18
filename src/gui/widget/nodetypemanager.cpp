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

#include "src/gui/widget/nodetypemanager.h"
#include <klocalizedstring.h>
#include "src/controller.h"

NodeTypeManager::NodeTypeManager()
{
	layout = new QGridLayout;
	layout->setAlignment(Qt::AlignTop);

	int row = 0;
	QLabel *caption = new QLabel("<h2>" + i18n("Node Types") + "</h2>");
	layout->addWidget(caption, row, 0);
	++row;

	QListWidget *typelist = new QListWidget;
	layout->addWidget(typelist, row, 0, 4, 1);
	++row;
	typelist->addItems(Controller::create()->getDataStore()->getNodeTypeNames());

	//TODO: icons
	QPushButton *btnAdd = new QPushButton(i18n("Add new Node Type"));
	layout->addWidget(btnAdd, row, 1);
	++row;
	QPushButton *btnEdit = new QPushButton(i18n("Edit"));
	layout->addWidget(btnEdit, row, 1);
	++row;
	QPushButton *btnDelete = new QPushButton(i18n("Delete"));
	layout->addWidget(btnDelete, row, 1);
	++row;

	QPushButton *btnExit = new QPushButton(i18n("Close"));
	layout->addWidget(btnExit, row, 0);
	connect(btnExit, SIGNAL(clicked()), this, SLOT(sendExit()));
	setLayout(layout);
}

NodeTypeManager::~NodeTypeManager()
{
	// TODO: implement
}

void NodeTypeManager::sendExit()
{
	emit exit();
}

