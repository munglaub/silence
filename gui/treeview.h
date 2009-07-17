#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDockWidget>

class TreeView : public QDockWidget
{
	public:
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();
};

#endif // TREEVIEW_H

