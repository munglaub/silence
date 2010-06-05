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

#ifndef NAVIGATIONSIDEBAR_H
#define NAVIGATIONSIDEBAR_H

#include <QDockWidget>
#include <QToolBar>
#include "src/data/node/node.h"
#include <QList>
#include <QAction>


/*!\class NavigationSidebar
 * \brief Helps navigating through the Nodes.
 *
 * This NavigationSidebar provides a previous and a next button to navigate through the last visited Nodes.
 *
 * \author Manuel Unglaub
 */
class NavigationSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NavigationSidebar which is a child of parent and has the provided window flags. The NavigationSidebar will be placed in the right dock widget area.
		 *
		 * The window title is set to title. This title is used when the NavigationSidebar is docked and undocked. It is also used in the context menu provided by MainWindow.
		 * The parameters will be passed to the QDockWidget constructro.
		 * \param title The title of the NavigationSidebar.
		 * \param parent The parent of this NavigationSidebar.
		 * \param flags The window flags of this NavigationSidebar.
		 */
		explicit NavigationSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NavigationSidebar();

	private slots:
		void selectionChanged(Node* node);
		void previous();
		void next();

	private:
		bool skip;
		QToolBar *toolbar;
		QAction *prevAction,
				*nextAction;

		QList<Node*> prevList;
		QList<Node*> nextList;

		void updateActions();
};

#endif // NAVIGATIONSIDEBAR_H

