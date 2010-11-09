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

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H


#include "kactioncollection.h"
#include <QHash>
#include <KAction>


//TODO: docu
class ActionManager
{
	public:
		ActionManager(KActionCollection *actioncollection);
		~ActionManager();

		KAction* getAction(QString name);
		KAction* getGlobalAction(QString name);
	
	private:
		KActionCollection *actioncollection;
		QHash<QString, KAction*> globalActions;
		QHash<QString, KAction*> actions;

		void createGlobalActions();
		KAction* addGlobalAction(QString name, QString text, bool checkable = false);

};

#endif // ACTIONMANAGER_H

