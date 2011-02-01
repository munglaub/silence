/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
 * Copyright (C) 2009, 2010 Yves Adler <yves.adler@googlemail.com>
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

#include <KIcon>
#include <klocalizedstring.h>
#include <QMenu>
#include <QPoint>
#include <QVariant>
#include "src/controller.h"
#include "src/data/node/richtextnodecontent.h"
#include "src/data/node/textnodecontent.h"
#include "src/gui/sidebar/treeview.h"


TreeView::TreeView(const QString &title, KActionCollection *actionCollection, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	setObjectName("TreeView");

	setupTree();
	setupQuestionFrame();
	setupToolbar(actionCollection);


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

	delete toolbar;
	delete layout;
	delete frame;
}

TreeModel* TreeView::getTreeModel()
{
	return model;
}

void TreeView::selectItem(QModelIndex &item)
{
	tree->selectionModel()->clearSelection();
	tree->selectionModel()->setCurrentIndex(item, QItemSelectionModel::Select);
	selectItem();
}

void TreeView::selectItem(NodeId id)
{
	QModelIndex index = model->findByNodeId(id.getId());
	if (index.isValid())
		selectItem(index);
}

void TreeView::addNode(QModelIndex &index, int row)
{
	NewNodeDialog *newDialog = new NewNodeDialog(index, row);
	Controller::create()->getMainWindow()->showDialog(newDialog);
	connect(newDialog, SIGNAL(done(NewNodeDialog*, bool)), this, SLOT(insertNode(NewNodeDialog*, bool)));
	// cancel dialog if parent is deleted
	connect(model->getItem(index), SIGNAL(destroyed(QObject*)), newDialog, SLOT(cancel()));
}

void TreeView::insertNode(NewNodeDialog *dlg, bool insert)
{
	if (insert)
	{
		QModelIndex index = dlg->getIndex();
		int row = dlg->getRow();
		if (model->insertRow(row, index))
		{
			int column = 0;
			QModelIndex child = model->index(row, column, index);

			model->setData(child, QVariant(dlg->getCaption()), Qt::EditRole);

			Node *item = model->getItem(child);
			item->setContent(dlg->getContent());
			item->addLabels(dlg->getLabels());
			connect(item, SIGNAL(changed(Node*)), Controller::create()->getDataStore(), SLOT(saveNode(Node*)));
			Controller::create()->getDataStore()->addNode(item);

			tree->selectionModel()->setCurrentIndex(model->index(row, column, index), QItemSelectionModel::ClearAndSelect);

			updateActions();
		}
	}

	Controller::create()->getMainWindow()->removeDialog(dlg);
	delete dlg;
}

void TreeView::showWelcomeView()
{
	// setting contentview to NULL will display welcomeview
	// TODO: find a more elegant solution
	Controller::create()->getContentView()->setNode(0);
}

void TreeView::setupToolbar(KActionCollection *actionCollection)
{
	toolbar = new QToolBar();

	addRowAction = actionCollection->addAction("addnode");
	addRowAction->setText(i18n("Add Node"));
	addRowAction->setIcon(KIcon("list-add"));
	toolbar->addAction(addRowAction);
	connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));

	addChildAction = actionCollection->addAction("addsubnode");
	addChildAction->setText(i18n("Add Subnode"));
	addChildAction->setIcon(KIcon("view-right-new"));
	toolbar->addAction(addChildAction);
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addChild()));

	removeAction = actionCollection->addAction("removenode");
	removeAction->setText(i18n("Remove Node"));
	removeAction->setIcon(KIcon("list-remove"));
	toolbar->addAction(removeAction);
	connect(removeAction, SIGNAL(triggered()), questionFrame, SLOT(show()));

	toolbar->addSeparator();

	propertyAction = actionCollection->addAction("shownodeproperties");
	propertyAction->setText(i18n("Properties"));
	propertyAction->setIcon(KIcon("document-properties"));
	toolbar->addAction(propertyAction);
	connect(propertyAction, SIGNAL(triggered()), Controller::create()->getNodePropertyWidget(), SLOT(show()));

	welcomeAction = actionCollection->addAction("showwelcomeview");
	welcomeAction->setText(i18n("Welcome View"));
	welcomeAction->setIcon(KIcon("silence"));
	toolbar->addAction(welcomeAction);
	connect(welcomeAction, SIGNAL(triggered(bool)), this, SLOT(showWelcomeView()));
}

void TreeView::setupTree()
{
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

	// All rows should have the same height so it should be no problem
	// to use this option. It should increace the performance of the TreeView.
	tree->setUniformRowHeights(true);

	tree->setDragEnabled(true);
	tree->setAcceptDrops(true);
	tree->setDropIndicatorShown(true);
	connect(model, SIGNAL(dropped(QModelIndex)), this, SLOT(nodeDropped(QModelIndex)));
}

void TreeView::setupQuestionFrame()
{
	questionFrame = new QGroupBox(i18n("Delete Node"));
	questionFrame->hide();
	questionLayout = new QGridLayout;

	icon = new QLabel();
	icon->setPixmap(KIcon("dialog-warning").pixmap(64, 64));
	questionLayout->addWidget(icon, 0, 0, 1, 1, Qt::AlignCenter);

	question = new QLabel(i18n("Are you sure?"));
	questionLayout->addWidget(question, 0, 1);

	yesButton = new QPushButton(i18n("Yes, delete Node"));
	questionLayout->addWidget(yesButton, 1, 0);

	noButton = new QPushButton(i18n("No, abort"));
	questionLayout->addWidget(noButton, 1, 1);

	questionFrame->setLayout(questionLayout);

	connect(noButton, SIGNAL(clicked(bool)), questionFrame, SLOT(hide()));
	connect(yesButton, SIGNAL(clicked(bool)), questionFrame, SLOT(hide()));
	connect(yesButton, SIGNAL(clicked(bool)), this, SLOT(removeTreeItem()));
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
		Controller::create()->getDataStore()->removeNode(model->getItem(index));
		updateActions();
	}
}

void TreeView::selectItem()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	Node *selectedNode = model->getItem(index);
	Controller *controller = Controller::create();
	controller->getContentView()->setNode(selectedNode);
	controller->getInfoSidebar()->setData(selectedNode);
	controller->getStatusBar()->setNodeName(selectedNode->getCaption());
	controller->getNodePropertyWidget()->setNode(selectedNode);
	questionFrame->hide();
	emit nodeSelected(selectedNode);
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

void TreeView::showTreeContextMenu()
{
	QMenu menu(this);
	menu.addAction(addRowAction);
	menu.addAction(addChildAction);
	menu.addAction(removeAction);
	menu.addAction(propertyAction);
	menu.exec(QCursor::pos());
}

void TreeView::nodeDropped(QModelIndex index)
{
	tree->selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
	Controller::create()->getDataStore()->saveNode(model->getItem(index));
}

