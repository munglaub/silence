#include "gui/mainwindow.h"
#include "gui/filemenu.h"
#include "gui/editmenu.h"
#include "gui/viewmenu.h"
#include "gui/helpmenu.h"
#include "gui/treeview.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <QMenuBar>

/*
	TODO:
	extract textedit and treeview, own class
	get/set for these components
	add meta-info-sidebar
	statusbar
*/


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// texteditor component
	textEdit = new QsciScintilla;
	// temporarily with a c++ lexer
	textEdit->setLexer(new QsciLexerCPP());
	setCentralWidget(textEdit);
	
	// the treeview on the left side
	addDockWidget(Qt::LeftDockWidgetArea, new TreeView(tr("Tree"), this));

	// set the initial windowsize
	resize(750, 500);
	
	// add menus
	menuBar()->addMenu(new FileMenu());
	menuBar()->addMenu(new EditMenu());
	menuBar()->addMenu(new ViewMenu());
	menuBar()->addMenu(new HelpMenu());
}   

MainWindow::~MainWindow()
{   
	delete textEdit;
}

