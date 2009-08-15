#include "gui/filemenu.h"
#include "gui/newnodedialog.h"
#include "gui/searchnodedialog.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&File"));
	QAction *newNode = addAction(tr("New Node"));
	connect(newNode, SIGNAL(triggered()), new NewNodeDialog, SLOT(exec()));
	addAction(tr("New Subnode"));

	addAction(tr("Rename Node"));
	addAction(tr("Move Node"));
	addAction(tr("Delete Node"));
	addSeparator();
	QAction *searchNode = addAction(tr("Search Node"));
	connect(searchNode, SIGNAL(triggered()), new SearchNodeDialog, SLOT(exec()));
	
	addAction(tr("Save"));
	addSeparator();
	QAction *exit = addAction(tr("&Exit"));
	connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

FileMenu::~FileMenu()
{
}

