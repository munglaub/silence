#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDockWidget>
#include <QTreeView>
#include "node/treemodel.h"

class TreeView : public QDockWidget
{
	Q_OBJECT

	public:
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();

	public slots:
		void updateActions();

	private slots:
		void addRow();
		void addChild();
		void removeTreeItem();
                
	private:
		QTreeView *tree;
		TreeModel *model;

		// Toolbar
		QAction *addRowAction;
		QAction *addChildAction;
		QAction *removeAction;
};

#endif // TREEVIEW_H

