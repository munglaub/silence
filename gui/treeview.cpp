#include "gui/contentview.h"
#include "gui/treeview.h"
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


TreeView::TreeView(const QString &title, ContentView *contentview, InfoSidebar *infosidebar, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	// Toolbar
	toolbar = new QToolBar();
	addRowAction = toolbar->addAction("add node");        
	connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction("add subnode");        
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addChild()));
	removeAction = toolbar->addAction("remove");
	connect(removeAction, SIGNAL(triggered()), this, SLOT(removeTreeItem()));

	// Tree
	tree = new QTreeView; 
	model = new TreeModel;
	tree->setModel(model);
	tree->setSelectionBehavior(QAbstractItemView::SelectItems);
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(updateActions()));

	this->contentview = contentview;
	this->infosidebar = infosidebar;
	// bin mir nicht sicher das das das beste signal ist
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(selectItem()));

	frame = new QFrame();
	layout = new QVBoxLayout;  
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
	QModelIndex index = tree->selectionModel()->currentIndex();

	if (!model->insertRow(index.row() + 1, index.parent()))
		return;

	updateActions();

	int column = 0;
	int pos = index.row() + 1;
	QModelIndex child = model->index(pos, column, index.parent());

	model->setData(child, QVariant("new Row"), Qt::EditRole);
	
	Node *item = model->getItem(child);
	item->setContent(new TextNodeContent);
	item->addLabel("foo");
	item->addLabel("bar");
	
	tree->selectionModel()->setCurrentIndex(model->index(pos, column, index.parent()),
		QItemSelectionModel::ClearAndSelect);
}

void TreeView::addChild()
{
	QModelIndex index = tree->selectionModel()->currentIndex();

	if (!model->insertRow(0, index))
		return;
	
	int column = 0;
	QModelIndex child = model->index(0, column, index);
	model->setData(child, QVariant("new Node"), Qt::EditRole);

	Node *item = model->getItem(child);
	item->setContent(new TextNodeContent);
	item->addLabel("text");
	item->addLabel("foobar");

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
	contentview->setContent(selectedNode->getContent());
	infosidebar->setData(selectedNode);
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

