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

#ifndef CMDMAIN_H
#define CMDMAIN_H

#include "src/data/node/node.h"


class CmdMain
{
	public:
		CmdMain();
		~CmdMain();

		void exec(int argc, char *argv[]);

	private:
		void printHelp();
		void printNode(int id);
		Node* findNodeById(int id, Node* root);
		void filterNodes(int argc, char *argv[], int pos);
		QDate strToDate(char *str);
};

#endif // CMDMAIN_H

