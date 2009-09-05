/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler
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
#include "node/treemodel.h"
#include "gui/searchnodesidebar.h"

#include <iostream>

SearchNodeSidebar::SearchNodeSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);

	searchedit = new QLineEdit;
	layout->addWidget(searchedit, 0, 0);

	filtermodel = new FilterModel;
	filtermodel->setSourceModel(Controller::create()->getTreeView()->getTree()->model());

	results = new QListView;
	results->setModel(filtermodel);
	layout->addWidget(results, 4, 0, 1, 2);

	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
	
	// Update search criterias
	connect(searchedit, SIGNAL(textChanged(QString)),
		filtermodel, SLOT(setFilterFixedString(QString)));

	// Update selections everywhere
	connect(results->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
		this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
}


void SearchNodeSidebar::selectionChanged(QModelIndex current, QModelIndex previous)
{
	QTreeView *tree = Controller::create()->getTreeView()->getTree();
	tree->selectionModel()->clearSelection();
	tree->selectionModel()->setCurrentIndex(filtermodel->mapToSource(current), QItemSelectionModel::Select);
	Controller::create()->getTreeView()->selectItem();
}


SearchNodeSidebar::~SearchNodeSidebar()
{
	delete layout;
	delete searchedit;
	delete results;
	delete frame;
}
