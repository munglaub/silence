#include "gui/treeview.h"
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>

TreeView::TreeView(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QTreeWidget *tree = new QTreeWidget();

	QTreeWidgetItem *first = new QTreeWidgetItem(tree, 0);
	first->setText(0, "blah");
	QTreeWidgetItem *firstsub = new QTreeWidgetItem(first, 0);
	firstsub->setText(0, "foobar");
	QTreeWidgetItem *sec = new QTreeWidgetItem(tree, 0);
	sec->setText(0, "blubb");

	setWidget(tree);
}

TreeView::~TreeView()
{
}

