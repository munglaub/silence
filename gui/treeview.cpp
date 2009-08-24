#include "gui/treeview.h"
#include "gui/newnodedialog.h"
#include "node/richtextnodecontent.h"
#include "node/textnodecontent.h"
#include "node/treemodel.h"
#include <QAction>
#include <QDockWidget>
#include <QList>
#include <QModelIndex>
#include <QStringList>
#include <QToolBar>
#include <QTreeView>
#include <QVariant>
#include <QVBoxLayout>
#include "controller.h"


TreeView::TreeView(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);


	// Toolbar
	toolbar = new QToolBar();
	addRowAction = toolbar->addAction("Add Node");        
	connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction("Add Subnode");        
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addChild()));
	removeAction = toolbar->addAction("Remove Node");
	connect(removeAction, SIGNAL(triggered()), this, SLOT(removeTreeItem()));

	// Tree
	tree = new QTreeView; 
	model = new TreeModel;
	tree->setModel(model);
	tree->setSelectionBehavior(QAbstractItemView::SelectItems);
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(updateActions()));

	// bin mir nicht sicher das das das beste signal ist
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(selectItem()));

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

void TreeView::addRow()
{
	NewNodeDialog *newDialog = new NewNodeDialog;
	if (!newDialog->exec())
	{
		delete newDialog;
		return;
	}

	QModelIndex index = tree->selectionModel()->currentIndex();

	if (!model->insertRow(index.row() + 1, index.parent()))
		return;

	updateActions();

	int column = 0;
	int pos = index.row() + 1;
	QModelIndex child = model->index(pos, column, index.parent());

	model->setData(child, QVariant(newDialog->getCaption()), Qt::EditRole);
	
	Node *item = model->getItem(child);
	item->setContent(newDialog->getContent());
	item->addLabels(newDialog->getLabels());

	delete newDialog;
	
	tree->selectionModel()->setCurrentIndex(model->index(pos, column, index.parent()),
		QItemSelectionModel::ClearAndSelect);
}

void TreeView::addChild()
{
	NewNodeDialog *newDialog = new NewNodeDialog;
	if (!newDialog->exec())
	{
		delete newDialog;
		return;
	}

	QModelIndex index = tree->selectionModel()->currentIndex();

	if (!model->insertRow(0, index))
		return;
	
	int column = 0;
	QModelIndex child = model->index(0, column, index);
	model->setData(child, QVariant(newDialog->getCaption()), Qt::EditRole);

	Node *item = model->getItem(child);
	item->setContent(newDialog->getContent());
	item->addLabels(newDialog->getLabels());

	// brauch ich das??
	if (!model->headerData(column, Qt::Horizontal).isValid())
		model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
							 Qt::EditRole);
	tree->selectionModel()->setCurrentIndex(model->index(0, 0, index),
		QItemSelectionModel::ClearAndSelect);
	
	updateActions();
}

void TreeView::removeTreeItem()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	QAbstractItemModel *model = tree->model();
	if (model->removeRow(index.row(), index.parent()))
		updateActions();
}

void TreeView::selectItem()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	Node *selectedNode = model->getItem(index);
	Controller *controller = Controller::create();
	controller->getContentView()->setContent(selectedNode->getContent());
	controller->getInfoSidebar()->setData(selectedNode);
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
