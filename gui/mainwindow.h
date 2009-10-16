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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "gui/menu/editmenu.h"
#include "gui/menu/helpmenu.h"
#include "gui/menu/nodemenu.h"
#include "gui/menu/silencemenu.h"
#include "gui/menu/viewmenu.h"
#include "gui/sidebar/infosidebar.h"
#include "gui/sidebar/nodepropertywidget.h"
#include "gui/sidebar/searchnodesidebar.h"
#include "gui/sidebar/treeview.h"
#include "gui/statusbar.h"
#include "gui/view/contentview.h"
#include <QMainWindow>


/*!\class MainWindow
 * \brief The main window of Silence.
 *
 * This is the Silence main window. It contains a central widget, several docking widgets and a statusbar.
 */

class MainWindow : public QMainWindow
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

	private:
		Controller *controller;
		ContentView *contentview;
		TreeView *treeview;
		InfoSidebar *infosidebar;
		SearchNodeSidebar *searchnodesidebar;
		StatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;

		// Menus
		SilenceMenu *silencemenu;
		NodeMenu *nodemenu;
		EditMenu *editmenu;
		ViewMenu *viewmenu;
		HelpMenu *helpmenu;
};

#endif // MAINWINDOW_H


