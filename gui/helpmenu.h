#ifndef HELPMENU_H
#define HELPMENU_H

#include "gui/aboutdialog.h"
#include <QAction>
#include <QMenu>


class HelpMenu : public QMenu
{
	Q_OBJECT

	public:
		HelpMenu(QWidget *parent = 0);
		~HelpMenu();

	private slots:
		void showAbout();

	private:
		QAction *about;
};

#endif // HELPMENU_H



