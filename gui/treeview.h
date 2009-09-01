#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "node/treemodel.h"
#include "gui/nodepropertywidget.h"
#include <QDockWidget>
#include <QFrame>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>
#include <QList>


class TreeView : public QDockWidget
{
	Q_OBJECT

	public:
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();
		QList<QAction*>* getNodeActions() const;

	public slots:
		void updateActions();

	protected:
		void contextMenuEvent(QContextMenuEvent *event);

	private slots:
		void addRow();
		void addChild();
		void removeTreeItem();
		void selectItem();
                
	private:
		QTreeView *tree;
		TreeModel *model;

		// Toolbar
		QToolBar *toolbar;
		QAction *addRowAction,
				*addChildAction,
				*removeAction,
				*propertyAction;
		

		QFrame *frame;
		QVBoxLayout *layout;

		void addNode(QModelIndex &index, int row);
};

#endif // TREEVIEW_H

