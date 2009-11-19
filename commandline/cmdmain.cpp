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

#include "commandline/cmdmain.h"
#include "controller.h"
#include <iostream>

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
					printNode(atoi(argv[i+1]));
					++i;
					break;
				case 's':
					// the big search
					break;
				case '-':
					cout << "langer parameter" << endl;
					break;
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
		cout << "nicht gefunden" << endl;
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


