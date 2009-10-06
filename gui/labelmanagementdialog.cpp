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

#include "gui/labelmanagementdialog.h"


LabelManagementDialog::LabelManagementDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("Label Management"));
	resize(300, 350);

	layout = new QGridLayout;
	int row = 0;

	toolbar = new QToolBar();
	addRowAction = toolbar->addAction(QIcon(":/icons/actions/list-add.png"), tr("Add Label"));
	addChildAction = toolbar->addAction(QIcon(":/icons/actions/view-right-new.png"), tr("Add Sublabel"));
	removeAction = toolbar->addAction(QIcon(":/icons/actions/list-remove.png"), tr("Remove Node"));
	
	layout->addWidget(toolbar, row, 0);
	++row;

	layout->addWidget(createInputFrame(), row, 0);
	++row;

	layout->addWidget(createDeleteFrame(), row, 0);
	++row;

	tree = new QTreeView;
	layout->addWidget(tree, row, 0);
	++row;

	closeBtn = new QPushButton(tr("Close"));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(accept()));
	layout->addWidget(closeBtn, row, 0, 1, 1, Qt::AlignRight);
	setLayout(layout);

	connect(addRowAction, SIGNAL(triggered()), inputFrame, SLOT(show()));
	connect(addChildAction, SIGNAL(triggered()), inputFrame, SLOT(show()));
	connect(removeAction, SIGNAL(triggered()), deleteFrame, SLOT(show()));
}

LabelManagementDialog::~LabelManagementDialog()
{
	//TODO: implement
}

QWidget* LabelManagementDialog::createInputFrame()
{
	inputFrame = new QGroupBox(tr("New Label"));
	inputFrame->hide();
	inputLayout = new QGridLayout;
	inputEdit = new QLineEdit;
	inputLayout->addWidget(inputEdit, 0, 0, 1, 2);
	cancelInputBtn = new QPushButton(tr("Cancel"));
	connect(cancelInputBtn, SIGNAL(clicked()), inputFrame, SLOT(hide()));
	inputLayout->addWidget(cancelInputBtn, 1, 0);
	okBtn = new QPushButton(tr("OK"));
	connect(okBtn, SIGNAL(clicked()), inputFrame, SLOT(hide()));
	inputLayout->addWidget(okBtn, 1, 1);
	inputFrame->setLayout(inputLayout);
	return inputFrame;
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
	connect(yesBtn, SIGNAL(clicked()), deleteFrame, SLOT(hide()));
	deleteLayout->addWidget(yesBtn, 1, 0);
	noBtn = new QPushButton(tr("No"));
	connect(noBtn, SIGNAL(clicked()), deleteFrame, SLOT(hide()));
	deleteLayout->addWidget(noBtn, 1, 1);
	deleteFrame->setLayout(deleteLayout);
	return deleteFrame;
}





