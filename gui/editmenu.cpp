#include "gui/editmenu.h"
#include <QMenu>
#include <QAction>

EditMenu::EditMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&Edit"));
}

EditMenu::~EditMenu()
{
}

