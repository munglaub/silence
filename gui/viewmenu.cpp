#include "gui/viewmenu.h"
#include <QMenu>
#include <QAction>

ViewMenu::ViewMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&View"));
	QAction *linewarp = addAction(tr("Linewarp"));
	linewarp->setCheckable(true);
	QAction *infosidebar = addAction(tr("Information Sidebar"));
	infosidebar->setCheckable(true);
	addAction(tr("Preferences"));

}

ViewMenu::~ViewMenu()
{
}

