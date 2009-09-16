/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub, Yves Adler
 *
 * This file is part of Silence.
 *
 * Silence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version GPLv2 only of the License.
 *
 * Silence is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	addRowAction = toolbar->addAction(QIcon(":/icons/actions/list-add.png"), tr("Add Node"));
        connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction(QIcon(":/icons/actions/view-right-new.png"), tr("Add Subnode"));
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addChild()));
	removeAction = toolbar->addAction(QIcon(":/icons/actions/list-remove.png"), tr("Remove Node"));

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

	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&,
			const QItemSelection&)),
			this, SLOT(selectItem()));

	// nodeproperty
	propertyAction = new QAction(tr("Properties"), this);
	connect(propertyAction, SIGNAL(triggered()), Controller::create()->getNodePropertyWidget(), SLOT(show()));

	// question frame
	question = new QLabel(tr("Are you sure?"));
	yesButton = new QPushButton(tr("Yes"));
	noButton = new QPushButton(tr("No"));
	
	questionFrame = new QGroupBox(tr("Delete Node"));
	questionFrame->hide();
	questionLayout = new QGridLayout;
	icon = new QLabel();
	icon->setPixmap(QPixmap(":/icons/status/dialog-warning.png"));
	questionLayout->addWidget(icon, 0, 0, 1, 1, Qt::AlignCenter);
	questionLayout->addWidget(question, 0, 1);
	questionLayout->addWidget(yesButton, 1, 0);
	questionLayout->addWidget(noButton, 1, 1);
	questionFrame->setLayout(questionLayout);

	connect(removeAction, SIGNAL(triggered()), questionFrame, SLOT(show()));
	connect(noButton, SIGNAL(clicked(bool)), questionFrame, SLOT(hide()));
	connect(yesButton, SIGNAL(clicked(bool)), questionFrame, SLOT(hide()));
	connect(yesButton, SIGNAL(clicked(bool)), this, SLOT(removeTreeItem()));	

	frame = new QFrame();
	layout = new QVBoxLayout;  
	layout->setContentsMargins(4, 0, 4, 4);
	layout->addWidget(toolbar);
	layout->addWidget(questionFrame);
	layout->addWidget(tree);
	frame->setLayout(layout);
	setWidget(frame);

	updateActions();
}

TreeView::~TreeView()
{      
	delete tree;
	delete model;

	delete question;
	delete yesButton;
	delete noButton;
	delete questionLayout;
	delete questionFrame;

	delete addRowAction;
	delete addChildAction;
	delete removeAction;
	delete toolbar;
	delete layout;
	delete frame;
}

QTreeView* TreeView::getTree()
{
	return tree;
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
	questionFrame->hide();
}

void TreeView::updateActions()
{
	bool hasSelection = !tree->selectionModel()->selection().isEmpty();
	removeAction->setEnabled(hasSelection);

	bool hasCurrent = tree->selectionModel()->currentIndex().isValid();
	addRowAction->setEnabled(hasCurrent);

	// TODO: is the following necessary?
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

