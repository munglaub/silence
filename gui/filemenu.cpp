#include "gui/filemenu.h"
#include "gui/newnodedialog.h"
#include "gui/searchnodedialog.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	controller = Controller::create();

	setTitle(tr("&File"));

	QList<QAction*> *actions = controller->getTreeView()->getNodeActions();
	for (int i=0; i<actions->size(); ++i)
		addAction(actions->at(i));

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

