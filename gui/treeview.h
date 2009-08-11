#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "gui/contentview.h"
#include "gui/infosidebar.h"
#include "node/treemodel.h"
#include <QDockWidget>
#include <QFrame>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>


class TreeView : public QDockWidget
{
	Q_OBJECT

	public:
		TreeView(const QString &title, ContentView *contentview, InfoSidebar *infoSidebar, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();

	public slots:
		void updateActions();

	private slots:
		void addRow();
		void addChild();
		void removeTreeItem();
		void selectItem();
                
	private:
		QTreeView *tree;
		TreeModel *model;
		ContentView *contentview;
		InfoSidebar *infosidebar;

		// Toolbar
		QToolBar *toolbar;
		QAction *addRowAction;
		QAction *addChildAction;
		QAction *removeAction;

		QFrame *frame;
		QVBoxLayout *layout;
};

#endif // TREEVIEW_H

