#include "gui/filemenu.h"
#include <QMenu>
#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&File"));
	addAction(tr("Save"));
	QAction *exit = addAction(tr("&Exit"));
	connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

FileMenu::~FileMenu()
{
}

