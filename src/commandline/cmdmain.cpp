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

#include "src/commandline/cmdmain.h"
#include "src/controller.h"
#include "src/commandline/nodefilter.h"
#include <iostream>
#include <stdio.h>

using namespace std;

CmdMain::CmdMain()
{
//	cout << "CmdMain()\n";
}

CmdMain::~CmdMain()
{
//	cout << "~CmdMain()\n";
}

void CmdMain::exec(int argc, char *argv[])
{
	int i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'h':
					printHelp();
					return;
				case 'i':
					++i;
					printNode(atoi(argv[i]));
					break;
				case 's':
					filterNodes(argc, argv, i);
					return;
					break;
//				case '-':
//					cout << "long parameter" << endl;
//					break;
				default:
					cout << "Unknown parameter" << endl;
					printHelp();
			}
		}
		++i;
	}
	
}

void CmdMain::printHelp()
{
	cout << "Some information about the silence command line options.." << endl;

	cout << "silence [-h | -i <id> | -s" << endl;
	cout << "\t( --text <text>" << endl;
	cout << "\t| --fulltext" << endl;
	cout << "\t| --created <from> <to>" << endl;
	cout << "\t| --modified <from> <to>" << endl;
	cout << "\t| --label <lbl1,lbl1,...>" << endl;
	cout << "\t| --nolabel <lbl1,lbl2,...>" << endl;
	cout << "\t| --type <type>) ... ]" << endl;
	cout << endl << endl;

	cout << "  -h\n\t Print this help" << endl;
	cout << "  -i <id>\n\t Print the node with <id>" << endl;
	cout << "  -s\n\t Search for nodes." << endl;
	cout << "\t--text <text>" << endl;
	cout << "\t\t Restrict the search to nodes which contain <text> in their caption or in their content if --fulltext is set." << endl;
	cout << "\t--fulltext" << endl;
	cout << "\t\t Use to search the content for the text provided by the --text option." << endl;
	cout << "\t--created <from> <to>" << endl;
	cout << "\t\t Restrict the search to nodes created between <from> and <to>." << endl;
	cout << "\t--modified <from> <to>" << endl;
	cout << "\t\t Restrict the search to nodes modified between <from> and <to>" << endl;
	cout << "\t--label <lbl1,lbl1,...>" << endl;
	cout << "\t\t Restrict the search to nodes which have all labels given by <lbl1,lbl2,...>" << endl;
	cout << "\t--nolabel <foo>" << endl;
	cout << "\t\t Restrict the search to nodes which do not have the labels given by <lbl1,lbl2,..>" << endl;
	cout << "\t--type <type>) ... ]" << endl;
	cout << "\t\t Restrict the search to nodes with a specific type. Available types are text/plain and text/richtext." << endl;

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

void CmdMain::filterNodes(int argc, char *argv[], int pos)
{

	NodeFilter *filter = new NodeFilter(Controller::create()->getDataStore()->getRootNode());
	for (int i = pos; i < argc; ++i)
	{
		if (QString(argv[i]) == "--text")
		{
			++i;
			filter->setFilterString(QString(argv[i]));
			continue;
		}
		if (QString(argv[i]) == "--fulltext")
			filter->enableFulltext(true);
		if (QString(argv[i]) == "--created")
		{
			++i;
			QDate from = strToDate(argv[i]);
			++i;
			QDate to = strToDate(argv[i]);
			if (!from.isValid() || !to.isValid())
			{
				//TODO: think about that again..
				cerr << "Error: Invalide Dates" << endl;
				return;
			}

			filter->setCreationDateFilter(from, to);
			continue;
		}
		if (QString(argv[i]) == "--modified")
		{
			++i;
			QDate from = strToDate(argv[i]);
			++i;
			QDate to = strToDate(argv[i]);
			if (!from.isValid() || !to.isValid())
			{
				//TODO: think about that again..
				cerr << "Error: Invalide Dates" << endl;
				return;
			}

			filter->setModificationDateFilter(from, to);
			continue;
		}
		if (QString(argv[i]) == "--label")
		{
			++i;
			filter->setLabelFilter(QString(argv[i]).split(","));
			continue;
		}
		if (QString(argv[i]) == "--nolabel")
		{
			++i;
			filter->setNoLabelFilter(QString(argv[i]).split(","));
			continue;
		}
		if (QString(argv[i]) == "--type")
		{
			++i;
			filter->setMimeTypFilter(QString(argv[i]));
			continue;
		}

	}
	filter->printNodes();
	delete filter;
}

QDate CmdMain::strToDate(char *str)
{
	int y, m, d;
	sscanf(str, "%d-%d-%d", &y, &m, &d);
	return QDate(y, m, d);
}


