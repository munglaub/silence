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

#ifndef VIEWMENU_H
#define VIEWMENU_H

#include <QMenu>

/*!\class ViewMenu
 * \brief Consists of actions to show/hide various sidebars and views.
 *
 * This menu consists of actions to show and hide the sidebars. It also can open the LabelManagementDialog and show the WelcomeView.
 *
 * \author Manuel Unglaub
 */

class ViewMenu : public QMenu
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the ViewMenu which is a child of parent.
		 * \param parent The parent of this ViewMenu.
		 */
		ViewMenu(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~ViewMenu();

	private slots:
		void showWelcomeView();
		void showLabelManagementDialog();
		void showNodeTree(bool visible);
		void showInfo(bool visible);
		void showProperties(bool visible);
		void showNodeSearch(bool visible);

	private:
		QAction	*welcomeViewAction,
				*showNodeTreeAction,
				*showInfoAction,
				*showPropertiesAction,
				*showNodeSearchAction,
				*showLabelManagementAction;
};

#endif // VIEWMENU_H



