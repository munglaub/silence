#include "gui/editmenu.h"
#include "gui/filemenu.h"
#include "gui/helpmenu.h"
#include "gui/infosidebar.h"
#include "gui/mainwindow.h"
#include "gui/statusbar.h"
#include "gui/textedit.h"
#include "gui/treeview.h"
#include "gui/viewmenu.h"
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Silence"));

	// texteditor component
	textedit = new TextEdit;
	setCentralWidget(textedit);
	
	// the treeview on the left side
	treeview = new TreeView(tr("Tree"), this);
	addDockWidget(Qt::LeftDockWidgetArea, treeview);

	// information sidebar to show the meta-infos
	infosidebar = new InfoSidebar(tr("Info"), this);
	addDockWidget(Qt::RightDockWidgetArea, infosidebar);

	statusbar = new StatusBar;
	setStatusBar(statusbar);

	// set the initial windowsize
	resize(950, 500);
	
	// add menus
	filemenu = new FileMenu;
	menuBar()->addMenu(filemenu);
	editmenu = new EditMenu;
	menuBar()->addMenu(editmenu);
	viewmenu = new ViewMenu;
	menuBar()->addMenu(viewmenu);
	helpmenu = new HelpMenu;
	menuBar()->addMenu(helpmenu);
}   

MainWindow::~MainWindow()
{   
	delete textedit;
	delete treeview;
	delete infosidebar;
	delete statusbar;

	delete filemenu;
	delete editmenu;
	delete viewmenu;
	delete helpmenu;
}

