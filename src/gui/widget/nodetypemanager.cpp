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
#include "src/data/node/customnodetypedefinition.h"
#include <klocalizedstring.h>
#include "src/controller.h"


NodeTypeManager::NodeTypeManager()
{
	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	nodetypespanel = new NodeTypesPanel;
	layout->addWidget(nodetypespanel);
	connect(nodetypespanel, SIGNAL(exit()), this, SLOT(sendExit()));
	connect(nodetypespanel, SIGNAL(addNodeType()), this, SLOT(showInputWidget()));
	connect(nodetypespanel, SIGNAL(editNodeType(QString)), this, SLOT(showNodeTypeBuilder(QString)));
	connect(nodetypespanel, SIGNAL(deleteNodeType(QString)), this, SLOT(deleteNodeType(QString)));

	inputwidget = new InputWidget;
	inputwidget->setVisible(false);
	layout->addWidget(inputwidget);
	connect(inputwidget, SIGNAL(done()), this, SLOT(addNodeType()));

	nodetypebuilder = new NodeTypeBuilder;
	nodetypebuilder->setVisible(false);
	layout->addWidget(nodetypebuilder);
	connect(nodetypebuilder, SIGNAL(close()), this, SLOT(hideNodeTypeBuilder()));

	setLayout(layout);
}

NodeTypeManager::~NodeTypeManager()
{
	// TODO: implement
}

void NodeTypeManager::sendExit()
{
	emit exit(this);
}

void NodeTypeManager::showInputWidget()
{
	inputwidget->show(i18n("Node Type Name"));
}

void NodeTypeManager::addNodeType()
{
	if (inputwidget->getInput().isEmpty())
		return;
	showNodeTypeBuilder(inputwidget->getInput());
}

void NodeTypeManager::deleteNodeType(QString name)
{
	//TODO: eine grosse warnung und willst-du-wirklich-abfrage!!!
	//TODO: alle nodes mit dem nodetype loeschen..
	// alternative -> gucken ob es nodes mit dem type gibt und wenn ja sagen das loeschen nicht geht weil es noch nodes gibt..
	Controller::create()->getDataStore()->removeCustomNodeType(name);
	nodetypespanel->updateTypeList();
}

void NodeTypeManager::showNodeTypeBuilder(QString customNodeTypeName)
{
	nodetypespanel->setVisible(false);
	inputwidget->setVisible(false);

	nodetypebuilder->show(Controller::create()->getDataStore()->getCustomNodeType(customNodeTypeName));
}

void NodeTypeManager::hideNodeTypeBuilder()
{
	Controller::create()->getDataStore()->saveCustomNodeType(nodetypebuilder->getCustomNodeTypeDefinition());
	nodetypespanel->updateTypeList();
	nodetypespanel->setVisible(true);
	nodetypebuilder->setVisible(false);
}



