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


NodeTypeManager::NodeTypeManager()
{
	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	ntp = new NodeTypesPanel;
	layout->addWidget(ntp);
	connect(ntp, SIGNAL(exit()), this, SLOT(sendExit()));
	//connect(ntp, SIGNAL(addNodeType()), this, SLOT(showNodeTypeBuilder()));
	connect(ntp, SIGNAL(addNodeType()), this, SLOT(addNodeType()));
	iw = new InputWidget;
	iw->setVisible(false);
	layout->addWidget(iw);
	connect(iw, SIGNAL(done()), this, SLOT(showNodeTypeBuilder()));

	ntb = new NodeTypeBuilder;
	ntb->setVisible(false);
	layout->addWidget(ntb);
	connect(ntb, SIGNAL(close()), this, SLOT(hideNodeTypeBuilder()));

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

void NodeTypeManager::addNodeType()
{
	iw->show(i18n("Node Type Name"));
}

void NodeTypeManager::showNodeTypeBuilder()
{
	//TODO:
	// - ueberpruefen ob es leer ist
	// - ueberpruefen ob es den namen schon gibt
	ntp->setVisible(false);
	iw->setVisible(false);
	ntb->show(iw->getInput());
}

void NodeTypeManager::hideNodeTypeBuilder()
{
	ntp->setVisible(true);
	ntb->setVisible(false);
}



