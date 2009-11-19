/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
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
#include "gui/dialog/labelmanagementdialog.h"
#include <QMenu>


LabelManagementDialog::LabelManagementDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("Label Management"));
	resize(300, 500);

	layout = new QGridLayout;
	int row = 0;

	toolbar = new QToolBar();
	addRowAction = toolbar->addAction(QIcon(":/icons/actions/list-add.png"), tr("Add Label"));
	connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction(QIcon(":/icons/actions/view-right-new.png"), tr("Add Sublabel"));
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addSublabel()));
	removeAction = toolbar->addAction(QIcon(":/icons/actions/list-remove.png"), tr("Remove Node"));
	
	layout->addWidget(toolbar, row, 0);
	++row;

	inputwidget = new InputWidget;
	inputwidget->hide();
	connect(inputwidget, SIGNAL(done()), this, SLOT(addLabel()));
	layout->addWidget(inputwidget, row, 0);
	++row;

	layout->addWidget(createDeleteFrame(), row, 0);
	++row;

	model = new LabelModel();
	tree = new QTreeView;
	tree->setModel(model);
	tree->expandAll();
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(tree, SIGNAL(customContextMenuRequested(const QPoint&)),
			this, SLOT(showTreeContextMenu()));
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
			this, SLOT(selectItem()));
	layout->addWidget(tree, row, 0);
	++row;

	closeBtn = new QPushButton(tr("Close"));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(accept()));
	layout->addWidget(closeBtn, row, 0, 1, 1, Qt::AlignRight);
	setLayout(layout);
	connect(removeAction, SIGNAL(triggered()), deleteFrame, SLOT(show()));
	updateActions();
}

LabelManagementDialog::~LabelManagementDialog()
{
	delete noBtn;
	delete yesBtn;
	delete messageLbl;
	delete icon;
	delete deleteLayout;
	delete deleteFrame;

	delete inputwidget;

	delete closeBtn;
	delete model;
	delete tree;
	delete removeAction;
	delete addChildAction;
	delete addRowAction;
	delete toolbar;
	delete layout;
}

QWidget* LabelManagementDialog::createDeleteFrame()
{
	deleteFrame = new QGroupBox(tr("Delete Label"));
	deleteFrame->hide();
	deleteLayout = new QGridLayout;
	icon = new QLabel();
	icon->setPixmap(QPixmap(":/icons/status/dialog-warning.png"));
	deleteLayout->addWidget(icon, 0, 0, 1, 1, Qt::AlignCenter);
	messageLbl = new QLabel(tr("Are you sure?"));
	deleteLayout->addWidget(messageLbl, 0, 1);
	yesBtn = new QPushButton(tr("Yes"));
	connect(yesBtn, SIGNAL(clicked()), this, SLOT(removeLabel()));
	deleteLayout->addWidget(yesBtn, 1, 0);
	noBtn = new QPushButton(tr("No"));
	connect(noBtn, SIGNAL(clicked()), deleteFrame, SLOT(hide()));
	deleteLayout->addWidget(noBtn, 1, 1);
	deleteFrame->setLayout(deleteLayout);
	return deleteFrame;
}

void LabelManagementDialog::showTreeContextMenu()
{
	QMenu menu(this);
	menu.addAction(addRowAction);
	menu.addAction(addChildAction);
	menu.addAction(removeAction);
	menu.exec(QCursor::pos());
}

void LabelManagementDialog::addLabel()
{
	inputwidget->hide();
	if (!model->insertRow(newLabelRow, newLabelParent))
		return;

	int column = 0;
	QModelIndex child = model->index(newLabelRow, column, newLabelParent);
	model->setData(child, QVariant(inputwidget->getInput()));
	Controller::create()->getDataStore()->addLabel(model->getItem(child));
	tree->selectionModel()->setCurrentIndex(model->index(newLabelRow, column, newLabelParent), QItemSelectionModel::ClearAndSelect);
	updateActions();
}

void LabelManagementDialog::addRow()
{
	newLabelParent = tree->selectionModel()->currentIndex();
	newLabelRow = newLabelParent.row() + 1;
	newLabelParent = newLabelParent.parent();
	inputwidget->show(tr("New Label"));
}

void LabelManagementDialog::addSublabel()
{
	newLabelParent = tree->selectionModel()->currentIndex();
	newLabelRow = 0;
	inputwidget->show(tr("New Sublabel"));
	updateActions();
}

void LabelManagementDialog::removeLabel()
{
	QModelIndex index = tree->selectionModel()->currentIndex();
	QStringList removedLabels = model->getItem(index)->toStringList();
	model->removeRow(index.row(), index.parent());
	Controller::create()->getDataStore()->removeLabel(model->getItem(index));
	deleteFrame->hide();
	updateActions();

	Label *rootLabel = Controller::create()->getDataStore()->getRootLabel();
	for (int i = 0; i < removedLabels.size(); ++i)
	{
		if (!rootLabel->contains(removedLabels.at(i)))
		{
			QList<Node*> nodes = Controller::create()->getDataStore()->getRootNode()->toNodeList();
			for (int j = 0; j < nodes.size(); ++j)
				nodes.at(j)->removeLabel(removedLabels.at(i));
		}
	}
}

void LabelManagementDialog::selectItem()
{
	inputwidget->hide();
	deleteFrame->hide();
	updateActions();
}

void LabelManagementDialog::updateActions()
{
	bool hasSelection = !tree->selectionModel()->selection().isEmpty();
	removeAction->setEnabled(hasSelection);

	bool hasCurrent = tree->selectionModel()->currentIndex().isValid();
	addRowAction->setEnabled(hasCurrent);
}




