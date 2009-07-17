#include "gui/helpmenu.h"
#include "gui/aboutdialog.h"
#include <QMenu>
#include <QAction>

HelpMenu::HelpMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&Help"));
	QAction *about = addAction(tr("About"));
	connect(about, SIGNAL(triggered()), new AboutDialog(), SLOT(exec()));
}

HelpMenu::~HelpMenu()
{
}

