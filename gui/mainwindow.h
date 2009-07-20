#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/filemenu.h"
#include "gui/editmenu.h"
#include "gui/viewmenu.h"
#include "gui/helpmenu.h"
#include "gui/textedit.h"
#include "gui/treeview.h"
#include "gui/infosidebar.h"
#include "gui/statusbar.h"

class MainWindow : public QMainWindow
{

	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();
	private:
		TextEdit *textedit;
		TreeView *treeview;
		InfoSidebar *infosidebar;
		StatusBar *statusbar;

		// Menus
		FileMenu *filemenu;
		EditMenu *editmenu;
		ViewMenu *viewmenu;
		HelpMenu *helpmenu;
};

#endif // MAINWINDOW_H


