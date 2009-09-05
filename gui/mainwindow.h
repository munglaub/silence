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
#include "gui/contentview.h"
#include "gui/editmenu.h"
#include "gui/filemenu.h"
#include "gui/helpmenu.h"
#include "gui/infosidebar.h"
#include "gui/nodepropertywidget.h"
#include "gui/statusbar.h"
#include "gui/treeview.h"
#include "gui/viewmenu.h"
#include <QMainWindow>


class MainWindow : public QMainWindow
{

	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
	private:
		Controller *controller;
		ContentView *contentview;
		TreeView *treeview;
		InfoSidebar *infosidebar;
		StatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;

		// Menus
		FileMenu *filemenu;
		EditMenu *editmenu;
		ViewMenu *viewmenu;
		HelpMenu *helpmenu;
};

#endif // MAINWINDOW_H


