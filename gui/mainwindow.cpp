#include "gui/mainwindow.h"
#include "gui/filemenu.h"
#include "gui/editmenu.h"
#include "gui/viewmenu.h"
#include "gui/helpmenu.h"
#include "gui/textedit.h"
#include "gui/treeview.h"
#include "gui/infosidebar.h"
#include "gui/statusbar.h"
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Silence"));

	// texteditor component
	setCentralWidget(new TextEdit());
	
	// the treeview on the left side
	addDockWidget(Qt::LeftDockWidgetArea, new TreeView(tr("Tree"), this));

	// information sidebar to show the meta-infos
	addDockWidget(Qt::RightDockWidgetArea, new InfoSidebar(tr("Info"), this));

	setStatusBar(new StatusBar());

	// set the initial windowsize
	resize(950, 500);
	
	// add menus
	menuBar()->addMenu(new FileMenu());
	menuBar()->addMenu(new EditMenu());
	menuBar()->addMenu(new ViewMenu());
	menuBar()->addMenu(new HelpMenu());
}   

MainWindow::~MainWindow()
{   
}

