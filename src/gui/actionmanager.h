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


#include <KAction>
#include "kactioncollection.h"
#include <QHash>


/*!\class ActionManager
 * \brief Manages the actions of this application.
 *
 * This ActionManager manages all the actions of this application. There are two kinds of actions.
 * One kind of actions are the global actions. These are actions which are almost always active and
 * might be shown at different locations (e.g. the action to show the WelcomeView).
 *
 * The other kind of actions are actions which are only within the context of a ContentView usefull.
 * For example the save actions. There should be only one save action for all the different ContentViews.
 * Each ContentView hast to make sure the actions only trigger an event when the ContentView is active.
 *
 * To get an action the constants from the contstants.h file should be used.
 *
 * \author Manuel Unglaub
 */
class ActionManager
{
	public:
		/*! The constructor.
		 * Constructs the ActionManager.
		 * \param actioncollection The KActionCollection which will be used to create the actions.
		 */
		ActionManager(KActionCollection *actioncollection);

		/*!
		 * Get the KAction with the provided name. The name should be a constant from constants.h.
		 * \param name The name of the action to get.
		 * \return The action with the provided name.
		 */
		KAction* getAction(QString name);

		/*!
		 * Get the global action with the provided name. The name should be a constant from constants.h.
		 * \param name The name of the action to get.
		 * \result The action with the provided name.
		 */
		KAction* getGlobalAction(QString name);
	
	private:
		KActionCollection *actioncollection;
		QHash<QString, KAction*> globalActions;
		QHash<QString, KAction*> actions;

		void createGlobalActions();
		void createActions();
		KAction* addGlobalAction(QString name, QString text, bool checkable = false);
		KAction* addAction(KStandardAction::StandardAction actionType, QString name);
		KAction* addAction(QString name, QString text, QIcon icon, bool checkable = false);

};

#endif // ACTIONMANAGER_H

