/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <iostream>
#include "src/commandline/cmdmain.h"
#include "src/commandline/nodefilter.h"
#include "src/controller.h"

using namespace std;

CmdMain::CmdMain(KCmdLineArgs *args)
{
	this->args = args;
}

CmdMain::~CmdMain()
{
	args->clear();
}

int CmdMain::exec()
{
	if (args->isSet("s"))
	{
		filterNodes();
		return 1;
	}
	if (args->isSet("i"))
	{
		printNode(args->getOption("i").toInt());
		return 1;
	}
	return -1;
}

void CmdMain::printNode(int id)
{
	Controller *controller = Controller::create();
	Node *root = controller->getDataStore()->getRootNode();	
	Node *node = findNodeById(id, root);

	if (node)
	{
		cout << node->toString().toStdString() << endl;
	} else {
		cout << "not found" << endl;
	}

	delete controller;
}

Node* CmdMain::findNodeById(int id, Node* root)
{
	Node* result = 0;
	for (int i=0; i<root->getChildCount() && !result; ++i)
	{
		if (root->getChild(i)->getId().getId() == id)
			return root->getChild(i);
		else
			result = findNodeById(id, root->getChild(i));
	}
	return result;
}

void CmdMain::filterNodes()
{
	NodeFilter *filter = new NodeFilter(Controller::create()->getDataStore()->getRootNode());

	if (args->isSet("text"))
		filter->setFilterString(args->getOption("text"));
	if (args->isSet("fulltext"))
		filter->enableFulltext(true);
	if (args->isSet("created"))
	{
		QDate from = strToDate(args->getOption("created").split(':').value(0));
		QDate to = strToDate(args->getOption("created").split(':').value(1));
		if (!from.isValid() || !to.isValid())
		{
			//TODO: think about that again..
			cerr << "Error: Invalide Dates" << endl;
			return;
		}
		filter->setCreationDateFilter(from, to);
	}
	if (args->isSet("modified"))
	{
		QDate from = strToDate(args->getOption("modified").split(':').value(0));
		QDate to = strToDate(args->getOption("modified").split(':').value(1));
		if (!from.isValid() || !to.isValid())
		{
			//TODO: think about that again..
			cerr << "Error: Invalide Dates" << endl;
			return;
		}
		filter->setModificationDateFilter(from, to);
	}
	if (args->isSet("label"))
		filter->setLabelFilter(args->getOption("label").split(','));
	if (args->isSet("banlabel"))
		filter->setNoLabelFilter(args->getOption("banlabel").split(','));
	if (args->isSet("type"))
		filter->setMimeTypFilter(args->getOption("type"));
	filter->printNodes();
	delete filter;
}

QDate CmdMain::strToDate(QString str)
{
	QStringList strlist = str.split('-');
	int y = strlist.value(0).toInt();
	int m = strlist.value(1).toInt();
	int d = strlist.value(2).toInt();
	return QDate(y, m, d);
}


