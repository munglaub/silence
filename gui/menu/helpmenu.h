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

#ifndef HELPMENU_H
#define HELPMENU_H

#include "gui/dialog/aboutdialog.h"
#include <QAction>
#include <QMenu>


/*!\class HelpMenu
 * \brief Consists of an action to show some information about Silence.
 *
 * This menus action can show informations about Silence.
 *
 * \author Manuel Unglaub
 */
class HelpMenu : public QMenu
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the HelpMenu which is a child of parent.
		 * \parm parent The parent of this HelpMenu.
		 */
		HelpMenu(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~HelpMenu();

	private slots:
		void showAbout();

	private:
		QAction *about;
};

#endif // HELPMENU_H



