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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <QStackedWidget>
#include "src/gui/menu/silencemenu.h"
#include "src/gui/menu/viewmenu.h"
#include "src/gui/sidebar/infosidebar.h"
#include "src/gui/sidebar/navigationsidebar.h"
#include "src/gui/sidebar/nodepropertywidget.h"
#include "src/gui/sidebar/searchnodesidebar.h"
#include "src/gui/sidebar/treeview.h"
#include "src/gui/sistatusbar.h"
#include "src/gui/view/contentview.h"


/*!\class MainWindow
 * \brief The main window of Silence.
 *
 * This is the Silence main window. It contains a central widget, several docking widgets and a statusbar.
 *
 * \author Manuel Unglaub
 */

class MainWindow : public KXmlGuiWindow
{
	Q_OBJECT

	public:
		/*! The constructor.
		 * Constructs the main window with statusbar, treeview, searchnodesidebar and infosidebar.
		 * \param parent specifies the widgets parent.
		 */
		MainWindow(QWidget *parent = 0);

		/*! The destructor.
		 * Destroys the main window with its components.
		 */
		~MainWindow();

		/*!
		 * Show a screen to manage the node types.
		 */
		void showNodeTypeManagement();

		/*!
		 * Show a widget as centralwidget. Use this instead of modal dialogs.
		 * \param widget The widget which will be shown as centralwidget.
		 */
		void showDialog(QWidget *widget);

		/*!
		 * Remove a previously with showDialog() added widget. It will not be deleted.
		 * \param widget The widget which will be removed.
		 */
		void removeDialog(QWidget *widget);

	private slots:
		void deleteFromCentralWidgetStack(QWidget *widget);

	private:
		QStackedWidget *centralwidgetstack;
		ContentView *contentview;
		TreeView *treeview;
		InfoSidebar *infosidebar;
		SearchNodeSidebar *searchnodesidebar;
		SiStatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;
		NavigationSidebar *navigationsidebar;

		// Menus
		ViewMenu *viewmenu;
		SilenceMenu *silencemenu;
};

#endif // MAINWINDOW_H


