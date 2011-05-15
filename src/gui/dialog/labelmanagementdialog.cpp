/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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
#include "src/controller.h"
#include "src/gui/dialog/labelmanagementdialog.h"


LabelManagementDialog::LabelManagementDialog(QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	layout = new QGridLayout;
	int row = 0;

	toolbar = new QToolBar();
	addRowAction = toolbar->addAction(KIcon("list-add"), i18n("Add Label"));
	connect(addRowAction, SIGNAL(triggered()), this, SLOT(addRow()));
	addChildAction = toolbar->addAction(KIcon("view-right-new"), i18n("Add Sublabel"));
	connect(addChildAction, SIGNAL(triggered()), this, SLOT(addSublabel()));
	removeAction = toolbar->addAction(KIcon("list-remove"), i18n("Remove Label"));
	
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
	tree->setDragEnabled(true);
	tree->setAcceptDrops(true);
	tree->setDropIndicatorShown(true);
	tree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(tree, SIGNAL(customContextMenuRequested(const QPoint&)),
			this, SLOT(showTreeContextMenu()));
	connect(tree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
			this, SLOT(selectItem()));
	layout->addWidget(tree, row, 0);
	++row;

	closeBtn = new QPushButton(i18n("Close"));
	closeBtn->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(onClose()));
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
	deleteFrame = new QGroupBox(i18n("Delete Label"));
	deleteFrame->hide();
	deleteLayout = new QGridLayout;
	icon = new QLabel();
	icon->setPixmap(KIcon("dialog-warning").pixmap(64, 64));
	deleteLayout->addWidget(icon, 0, 0, 1, 1, Qt::AlignCenter);
	messageLbl = new QLabel(i18n("Are you sure?"));
	deleteLayout->addWidget(messageLbl, 0, 1);
	yesBtn = new QPushButton(i18n("Yes, delete Label"));
	connect(yesBtn, SIGNAL(clicked()), this, SLOT(removeLabel()));
	deleteLayout->addWidget(yesBtn, 1, 0);
	noBtn = new QPushButton(i18n("No, abort"));
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
	inputwidget->show(i18n("New Label"));
}

void LabelManagementDialog::addSublabel()
{
	newLabelParent = tree->selectionModel()->currentIndex();
	newLabelRow = 0;
	inputwidget->show(i18n("New Sublabel"));
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

void LabelManagementDialog::onClose()
{
	emit exit(this);
}




