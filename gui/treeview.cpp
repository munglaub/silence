#include "controller.h"
#include "gui/newnodedialog.h"
#include "gui/treeview.h"
#include "node/richtextnodecontent.h"
#include "node/textnodecontent.h"
#include "node/treemodel.h"
#include <QAction>
#include <QContextMenuEvent>
#include <QDockWidget>
#include <QList>
#include <QMessageBox>
#include <QModelIndex>
#include <QStringList>
#include <QToolBar>
#include <QTreeView>
#include <QVariant>
#include <QVBoxLayout>
#include <QPoint>


TreeView::TreeView(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);


	// Toolbar
	toolbar = new QToolBar();
	addRowAction = toolbar->addAction(QIcon("icons/list-add.png"), tr("Add Node"));
        connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction(QIcon("icons/view-right-new.png"), tr("Add Subnode"));        
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addChild()));
	removeAction = toolbar->addAction(QIcon("icons/list-remove.png"), tr("Remove Node"));
	connect(removeAction, SIGNAL(triggered()), this, SLOT(removeTreeItem()));

	// Tree
	tree = new QTreeView; 
	model = new TreeModel;
	tree->setModel(model);
	tree->setSelectionBehavior(QAbstractItemView::SelectItems);
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(updateActions()));
	
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(tree, SIGNAL(customContextMenuRequested (const QPoint&)),
			this, SLOT(showTreeContextMenu()));

	// bin mir nicht sicher das das das beste signal ist
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(selectItem()));

	// nodeproperty
	propertyAction = new QAction(tr("Properties"), this);
	connect(propertyAction, SIGNAL(triggered()), Controller::create()->getNodePropertyWidget(), SLOT(show()));

	frame = new QFrame();
	layout = new QVBoxLayout;  
	layout->setContentsMargins(8, 0, 0, 0);
	layout->addWidget(toolbar);
	layout->addWidget(tree);
	frame->setLayout(layout);
	setWidget(frame);

	updateActions();
}

TreeView::~TreeView()
{      
	delete tree;
	delete model;
	delete addRowAction;
	delete addChildAction;
	delete removeAction;
	delete toolbar;
	delete layout;
	delete frame;
}

void TreeView::addNode(QModelIndex &index, int row)
{
	NewNodeDialog *newDialog = new NewNodeDialog;
	if (!newDialog->exec())
	{
		delete newDialog;
		return;
	}

	if (!model->insertRow(row, index))
	{
		delete newDialog;
		return;
	}

	int column = 0;
	QModelIndex child = model->index(row, column, index);

	model->setData(child, QVariant(newDialog->getCaption()), Qt::EditRole);

	Node *item = model->getItem(child);
	item->setContent(newDialog->getContent());
	item->addLabels(newDialog->getLabels());
	connect(item, SIGNAL(changed(Node*)), Controller::create()->getDataStore(), SLOT(save(Node*)));
	Controller::create()->getDataStore()->add(item);

	delete newDialog;

	tree->selectionModel()->setCurrentIndex(model->index(row, column, index),
		QItemSelectionModel::ClearAndSelect);
	
	updateActions();
}

void TreeView::addRow()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	int row = index.row() + 1;
	index = index.parent();
	addNode(index, row);
}

void TreeView::addChild()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	int row = 0;
	addNode(index, row);
}

void TreeView::removeTreeItem()
{
	int ret = QMessageBox::question(this, tr("Delete Node"), tr("Are you sure?"), 
			  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (ret == QMessageBox::No)
		return;

	QModelIndex index = tree->selectionModel()->currentIndex();
	if (model->removeRow(index.row(), index.parent()))
	{
		Controller::create()->getDataStore()->remove(model->getItem(index));
		updateActions();
	}
}

void TreeView::selectItem()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	Node *selectedNode = model->getItem(index);
	Controller *controller = Controller::create();
	controller->getContentView()->setContent(selectedNode->getContent());
	controller->getInfoSidebar()->setData(selectedNode);
	controller->getStatusBar()->setNodeName(selectedNode->getCaption());
	controller->getNodePropertyWidget()->setNode(selectedNode);
}

void TreeView::updateActions()
{
	bool hasSelection = !tree->selectionModel()->selection().isEmpty();
	removeAction->setEnabled(hasSelection);

	bool hasCurrent = tree->selectionModel()->currentIndex().isValid();
	addRowAction->setEnabled(hasCurrent);

	// mh, brauch ich das??
	if (hasCurrent)
		tree->closePersistentEditor(tree->selectionModel()->currentIndex());
}

QList<QAction*>* TreeView::getNodeActions() const
{
	QList<QAction*> *result = new QList<QAction*>;
	result->append(addRowAction);
	result->append(addChildAction);
	result->append(removeAction);
	return result;
}

void TreeView::showTreeContextMenu()
{
	QMenu menu(this);
	menu.addAction(addRowAction);
	menu.addAction(addChildAction);
	menu.addAction(removeAction);
	menu.addAction(propertyAction);
	menu.exec(QCursor::pos());
}

