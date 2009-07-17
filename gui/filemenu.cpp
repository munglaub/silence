#include "gui/filemenu.h"
#include "gui/newnodedialog.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&File"));
	QAction *newNode = addAction(tr("New Node"));
	connect(newNode, SIGNAL(triggered()), new NewNodeDialog(), SLOT(exec()));

	addAction(tr("Rename Node"));
	addAction(tr("Move Node"));
	addAction(tr("Delete Node"));
	addSeparator();
	addAction(tr("Search Node"));
	addAction(tr("Save"));
	addSeparator();
	QAction *exit = addAction(tr("&Exit"));
	connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

FileMenu::~FileMenu()
{
}

