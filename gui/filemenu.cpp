#include "gui/filemenu.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&File"));
	addAction(tr("New Node"));
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

