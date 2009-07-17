#include "gui/editmenu.h"
#include <QMenu>
#include <QAction>

EditMenu::EditMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&Edit"));
	addAction(tr("Undo"));
	addAction(tr("Redo"));
	addSeparator();
	addAction(tr("Copy"));
	addAction(tr("Cut"));
	addAction(tr("Paste"));
	addAction(tr("Select All"));
	addSeparator();
	addAction(tr("Search"));
	addAction(tr("Replace"));
}

EditMenu::~EditMenu()
{
}

