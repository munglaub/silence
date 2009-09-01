#include "gui/contentview.h"
#include "gui/editmenu.h"
#include "gui/filemenu.h"
#include "gui/helpmenu.h"
#include "gui/infosidebar.h"
#include "gui/mainwindow.h"
#include "gui/statusbar.h"
#include "gui/treeview.h"
#include "gui/viewmenu.h"
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Silence"));
	controller = Controller::create();

	// ContentView
	contentview = new ContentView;
	setCentralWidget(contentview);
	controller->setContentView(contentview);


	// information sidebar to show the meta-infos
	infosidebar = new InfoSidebar(tr("Info"), this);
	addDockWidget(Qt::RightDockWidgetArea, infosidebar);
	controller->setInfoSidebar(infosidebar);

	nodepropertywidget = new NodePropertyWidget(tr("Properties"), this);
//	nodepropertywidget->hide();
	addDockWidget(Qt::RightDockWidgetArea, nodepropertywidget);
	controller->setNodePropertyWidget(nodepropertywidget);

	// the treeview on the left side
	treeview = new TreeView(tr("Tree"), this);
	addDockWidget(Qt::LeftDockWidgetArea, treeview);
	controller->setTreeView(treeview);

	statusbar = new StatusBar;
	setStatusBar(statusbar);
	controller->setStatusBar(statusbar);

	// set the initial windowsize
	resize(950, 500);
	
	// add menus
	filemenu = new FileMenu;
	menuBar()->addMenu(filemenu);
	editmenu = new EditMenu;
	menuBar()->addMenu(editmenu);
	controller->setEditMenu(editmenu);
	viewmenu = new ViewMenu;
	menuBar()->addMenu(viewmenu);
	helpmenu = new HelpMenu;
	menuBar()->addMenu(helpmenu);
}   

MainWindow::~MainWindow()
{   
	delete contentview;
	delete treeview;
	delete infosidebar;
	delete statusbar;
	delete nodepropertywidget;

	delete filemenu;
	delete editmenu;
	delete viewmenu;
	delete helpmenu;

	delete controller;
}

