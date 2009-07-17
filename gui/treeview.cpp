#include "gui/treeview.h"
#include <QDockWidget>
#include <QTreeView>

TreeView::TreeView(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QTreeView *tree = new QTreeView();
	setWidget(tree);
}

TreeView::~TreeView()
{
}

