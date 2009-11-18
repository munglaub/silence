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

#ifndef NODEMENU_H
#define NODEMENU_H

#include <QMenu>

/*!\class NodeMenu
 * \brief Consists of actions related to the nodes.
 *
 * This menu consists of node related actions like add and remove node. It shares this actions with other components like the TreeView.
 *
 * \author Manuel Unglaub
 */
class NodeMenu : public QMenu
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NodeMenu which is a child of parent. This menu gets its actions from the TreeView with help of the Controller.
		 * \param parent The parent of this NodeMenu.
		 */
		NodeMenu(QWidget *parent = 0);
};

#endif // NODEMENU_H



