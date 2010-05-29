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

#ifndef CMDMAIN_H
#define CMDMAIN_H

#include <kcmdlineargs.h>
#include "src/data/node/node.h"


class CmdMain
{
	public:
		CmdMain(KCmdLineArgs *args);
		~CmdMain();

		int exec();

	private:
		KCmdLineArgs *args;

		void printNode(int id);
		Node* findNodeById(int id, Node* root);
		void filterNodes();
		QDate strToDate(QString str);
};

#endif // CMDMAIN_H

