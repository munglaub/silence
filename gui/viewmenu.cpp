#include "gui/viewmenu.h"
#include <QMenu>
#include <QAction>

ViewMenu::ViewMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&View"));
	QAction *linewarp = addAction(tr("Linewarp"));
	linewarp->setCheckable(true);
	linewarp->setEnabled(false);
	QAction *infosidebar = addAction(tr("Information Sidebar"));
	infosidebar->setCheckable(true);
	infosidebar->setEnabled(false);
	QAction *preferences = addAction(tr("Preferences"));
	preferences->setEnabled(false);

}

ViewMenu::~ViewMenu()
{
}

