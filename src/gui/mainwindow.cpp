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

#include <kactioncollection.h>
#include <kaction.h>
#include <klocalizedstring.h>
#include <KMenuBar>
#include <QApplication>
#include "src/gui/mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: KXmlGuiWindow(parent)
{
	setWindowTitle(i18n("Silence"));
	controller = Controller::create();

	// ContentView
	contentview = new ContentView;
	setCentralWidget(contentview);
	controller->setContentView(contentview);


	nodepropertywidget = new NodePropertyWidget(i18n("Properties"), this);
	nodepropertywidget->hide();
	controller->setNodePropertyWidget(nodepropertywidget);

	// the treeview on the left side
	treeview = new TreeView(i18n("Nodes"), actionCollection(), this);
	controller->setTreeView(treeview);

	// search sidebar
	searchnodesidebar = new SearchNodeSidebar(i18n("Search Nodes"), this);
	controller->setSearchNodeSidebar(searchnodesidebar);

	// navigation sidebar
	navigationsidebar = new NavigationSidebar(i18nc("title of the navigation sidebar", "Navigation"), this);
	controller->setNavigationSidebar(navigationsidebar);

	// information sidebar to show the metainfos
	infosidebar = new InfoSidebar(i18n("Information"), this);
	controller->setInfoSidebar(infosidebar);

	// docking the widgets
	addDockWidget(Qt::RightDockWidgetArea, navigationsidebar);
	addDockWidget(Qt::RightDockWidgetArea, infosidebar);
	addDockWidget(Qt::LeftDockWidgetArea, treeview);
	addDockWidget(Qt::LeftDockWidgetArea, treeview);
	tabifyDockWidget(treeview, searchnodesidebar);
	addDockWidget(Qt::LeftDockWidgetArea, nodepropertywidget);

	statusbar = new SiStatusBar;
	setStatusBar(statusbar);
	controller->setStatusBar(statusbar);

	controller->setActionCollection(actionCollection());

	controller->getTextEdit()->setVisible(false);
	controller->getRichTextEdit()->setVisible(false);

	viewmenu = new ViewMenu(actionCollection());
	KAction *action = actionCollection()->addAction("exit");
	action->setText(i18n("&Exit"));
	action->setIcon(KIcon("application-exit"));
	connect(action, SIGNAL(triggered()), qApp, SLOT(quit()));

	setupGUI(QSize(1100, 600), Keys | StatusBar | Save | Create);
}

MainWindow::~MainWindow()
{   
	delete contentview;
	delete treeview;
	delete infosidebar;
	delete statusbar;
	delete nodepropertywidget;
	delete searchnodesidebar;

	delete viewmenu;

	delete controller;
}

