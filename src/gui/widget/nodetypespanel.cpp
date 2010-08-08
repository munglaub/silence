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

#include "src/gui/widget/nodetypespanel.h"
#include "src/controller.h"
#include <klocalizedstring.h>


NodeTypesPanel::NodeTypesPanel()
{
	layout = new QGridLayout;
	layout->setAlignment(Qt::AlignTop);

	int row = 0;
	caption = new QLabel("<h2>" + i18n("Custom Node Types") + "</h2>");
	layout->addWidget(caption, row, 0);
	++row;

	typelist = new QListWidget;
	layout->addWidget(typelist, row, 0, 4, 1);
	++row;
	typelist->addItems(Controller::create()->getDataStore()->getCustomNodeTypeNames());

	btnAdd = new QPushButton(i18n("Add new Node Type"));
	layout->addWidget(btnAdd, row, 1);
	++row;
	connect(btnAdd, SIGNAL(clicked()), this, SLOT(addType()));

	btnEdit = new QPushButton(i18n("Edit Node Type"));
	layout->addWidget(btnEdit, row, 1);
	++row;
	connect(btnEdit, SIGNAL(clicked()), this, SLOT(editType()));

	btnDelete = new QPushButton(i18n("Delete Node Type"));
	layout->addWidget(btnDelete, row, 1);
	++row;
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteType()));

	btnExit = new QPushButton(i18n("Close"));
	btnExit->setMinimumWidth(100);
	layout->addWidget(btnExit, row, 0, 1, 1, Qt::AlignRight);
	connect(btnExit, SIGNAL(clicked()), this, SLOT(sendExit()));
	setLayout(layout);

	connect(typelist, SIGNAL(itemSelectionChanged()), this, SLOT(updateButtons()));
	updateButtons();
}

NodeTypesPanel::~NodeTypesPanel()
{
	delete btnExit;
	delete btnDelete;
	delete btnEdit;
	delete btnAdd;
	delete typelist;
	delete caption;
	delete layout;
}

void NodeTypesPanel::updateTypeList()
{
	typelist->clear();
	typelist->addItems(Controller::create()->getDataStore()->getCustomNodeTypeNames());
}

void NodeTypesPanel::sendExit()
{
	emit exit();
}

void NodeTypesPanel::addType()
{
	emit addNodeType();
}

void NodeTypesPanel::editType()
{
	emit editNodeType(typelist->currentItem()->text());
}

void NodeTypesPanel::deleteType()
{
	emit deleteNodeType(typelist->currentItem()->text());
}

void NodeTypesPanel::updateButtons()
{
	if (typelist->selectedItems().isEmpty())
	{
		btnEdit->setEnabled(false);
		btnDelete->setEnabled(false);
	} else {
		btnEdit->setEnabled(true);
		btnDelete->setEnabled(true);
	}
}

