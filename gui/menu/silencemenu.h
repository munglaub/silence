/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler, Manuel Unglaub
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

#ifndef SILENCEMENU_H
#define SILENCEMENU_H

#include <QMenu>


/*!\class SilenceMenu
 * \brief The main menu of the application.
 *
 * Provides actions to exit the application and to access the preferences.
 *
 * \authors Yves Adler, Manuel Unglaub
 */
class SilenceMenu : public QMenu
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the SilenceMenu which is a child of parent.
		 * \param parent The parent of this SilenceMenu.
		 */
		SilenceMenu(QWidget *parent = 0);

		/*! The destruktor.
		 *
		 * Destroys the object.
		 */
		~SilenceMenu();

	private:
		QAction *preferences,
				*exit;
};

#endif // SILENCEMENU_H



