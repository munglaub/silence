#include "gui/helpmenu.h"

HelpMenu::HelpMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&Help"));
	about = addAction(tr("About"));
	connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

HelpMenu::~HelpMenu()
{
	delete about;
}

void HelpMenu::showAbout()
{
	AboutDialog *dlg = new AboutDialog;
	dlg->exec();
	delete dlg;
}

