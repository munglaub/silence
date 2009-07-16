#include "gui/mainwindow.h"
#include "gui/filemenu.h"
#include "gui/helpmenu.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <QTreeView>
#include <QDockWidget>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// texteditor component
	textEdit = new QsciScintilla;
	// temporarily with a c++ lexer
	textEdit->setLexer(new QsciLexerCPP());
	setCentralWidget(textEdit);
	
	// the treeview on the left side
	QTreeView *tree = new QTreeView();
	QDockWidget *dockWidget = new QDockWidget(tr("Tree"), this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | 
	Qt::RightDockWidgetArea);
	dockWidget->setWidget(tree);
	addDockWidget(Qt::LeftDockWidgetArea, dockWidget);


	// set the initial windowsize
	resize(750, 500);
	
	menuBar()->addMenu(new FileMenu());
	menuBar()->addMenu(new HelpMenu());
}   

MainWindow::~MainWindow()
{   
	delete textEdit;
}

