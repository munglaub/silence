#include "gui/mainwindow.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <QTreeView>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>

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


	// the main menu
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(tr("blah"));
	fileMenu->addAction(tr("blubb"));
	fileMenu->addAction(tr("foo"));
	fileMenu->addAction(tr("bar"));
	fileMenu->addAction(tr("foobar"));
}   

MainWindow::~MainWindow()
{   
	delete textEdit;
}


