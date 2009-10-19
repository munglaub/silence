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

#ifndef EDITMENU_H
#define EDITMENU_H

#include <QMenu>

/*!\class EditMenu
 * \brief Contains the actions related to editing the content of the nodes.
 *
 * Per default the EditMenu does not contain any actions. The contentviews are responsible to add the actions they need to the EditMenu and make them in-/visible when they are in-/active.
 *
 * \author Manuel Unglaub
 */

class EditMenu : public QMenu
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the EditMenu which is a child of parent.
		 * \param parent The parent of this EditMenu.
		 */
		EditMenu(QWidget *parent = 0);
};

#endif // FILEMENU_H



