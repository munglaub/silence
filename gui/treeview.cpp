#include "gui/treeview.h"
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QToolBar>
#include <QVBoxLayout>
#include <QAction>
#include <QList>
#include <QTreeWidgetItem>

TreeView::TreeView(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        QToolBar *toolbar = new QToolBar();
        
        QAction *addAction = toolbar->addAction("add");        
        connect(addAction, SIGNAL(triggered()), this, SLOT(addTreeItem()));
        QAction *removeAction = toolbar->addAction("remove");
        connect(removeAction, SIGNAL(triggered()), this, SLOT(removeTreeItem()));
        
        tree = new QTreeWidget; 

	QTreeWidgetItem *first = new QTreeWidgetItem(tree, 0);
	first->setText(0, "blah");
	QTreeWidgetItem *firstsub = new QTreeWidgetItem(first, 0);
	firstsub->setText(0, "foobar");
	QTreeWidgetItem *sec = new QTreeWidgetItem(tree, 0);
	sec->setText(0, "blubb");

        QFrame *frame = new QFrame();
        QVBoxLayout *layout = new QVBoxLayout;  
        layout->addWidget(toolbar);
        layout->addWidget(tree);
        frame->setLayout(layout);
        setWidget(frame);
}

void TreeView::addTreeItem()
{
        QTreeWidgetItem *newItem = new QTreeWidgetItem(tree, 0);
        newItem->setText(0, "testing");
}


void TreeView::removeTreeItem()
{
        QTreeWidgetItem *newItem = new QTreeWidgetItem(tree, 0);
        newItem->setText(0, "ich bin ein fieser segfault :)");
}


TreeView::~TreeView()
{      
        delete tree;
}

