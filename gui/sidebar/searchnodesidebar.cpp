/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler, Manuel Unglaub
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
#include "data/model/treemodel.h"
#include "gui/sidebar/searchnodesidebar.h"


SearchNodeSidebar::SearchNodeSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(title, parent, flags)
{
	// Setup the listproxy, which basically transforms the tree into a flat strcuture
	listProxy = new ListProxyModel;
	QAbstractItemModel *treemodel = Controller::create()->getTreeView()->getTreeModel();
	listProxy->setSourceModel(treemodel);
	// update the proxy when nodes are added or removed
	connect(treemodel, SIGNAL(rowsInserted(const QModelIndex&, int, int)), listProxy, SLOT(update()));
	connect(treemodel, SIGNAL(rowsRemoved(const QModelIndex&, int, int)), listProxy, SLOT(update()));

	// setup the filtermodel first, as everything else will connect to it
	filtermodel = new FilterModel;
	filtermodel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filtermodel->setSourceModel(listProxy);

	connect(this, SIGNAL(visibilityChanged(bool)), filtermodel, SLOT(invalidate()));

	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	int row = 0;

	searchedit = new QLineEdit;
	layout->addWidget(searchedit, row, 0);
	++row;

	searchnodeoptions = new SearchNodeOptions();
	layout->addWidget(searchnodeoptions, row, 0);
	++row;

	labellist = new LabelList;
	layout->addWidget(labellist, row, 0);
	++row;

	connectOptions();
	connectLabelList();

	// setup the resultlist
	resultList = new QListView;
	resultList->setModel(filtermodel);
	layout->addWidget(resultList, row, 0);
	++row;

	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
	
	// Update search criterias
	connect(searchedit, SIGNAL(textChanged(QString)),
		filtermodel, SLOT(setFilterFixedString(QString)));

	// Update selections everywhere
	connect(resultList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
		this, SLOT(selectionChanged(QModelIndex)));
}

SearchNodeSidebar::~SearchNodeSidebar()
{
	delete searchedit;
	delete resultList;
	delete labellist;
	delete searchnodeoptions;

	delete layout;
	delete frame;

	delete filtermodel;
	delete listProxy;
}

void SearchNodeSidebar::updateLabels()
{
	labellist->update();
}

void SearchNodeSidebar::selectionChanged(QModelIndex current)
{
	QModelIndex sourceIndex = filtermodel->mapToSource(current);
	Controller::create()->getTreeView()->selectItem(sourceIndex);
}

void SearchNodeSidebar::connectOptions()
{
	connect(searchnodeoptions, SIGNAL(enabledFulltext(bool)), filtermodel, SLOT(setFilterFulltextEnabled(bool)));
	connect(searchnodeoptions, SIGNAL(enabledMimetype(bool)), filtermodel, SLOT(setFilterMimetypeEnabled(bool)));
	connect(searchnodeoptions, SIGNAL(enabledCreationDate(bool)), filtermodel, SLOT(setFilterCreatedDateEnabled(bool)));
	connect(searchnodeoptions, SIGNAL(enabledModificationDate(bool)), filtermodel, SLOT(setFilterModifiedDateEnabled(bool)));
	connect(searchnodeoptions, SIGNAL(mimetypeSelected(QString)), filtermodel, SLOT(setFilterMimetypeString(const QString&)));
	connect(searchnodeoptions, SIGNAL(changedCreatedFrom(QDate)), filtermodel, SLOT(setFilterCreatedFromDate(const QDate&)));
	connect(searchnodeoptions, SIGNAL(changedCreatedTo(QDate)), filtermodel, SLOT(setFilterCreatedToDate(const QDate&)));
	connect(searchnodeoptions, SIGNAL(changedModifiedFrom(QDate)), filtermodel, SLOT(setFilterModifiedFromDate(const QDate&)));
	connect(searchnodeoptions, SIGNAL(changedModifiedTo(QDate)), filtermodel, SLOT(setFilterModifiedToDate(const QDate&)));
}

void SearchNodeSidebar::connectLabelList()
{
	connect(labellist, SIGNAL(addedLabel(QString)), filtermodel, SLOT(addLabel(QString)));
	connect(labellist, SIGNAL(removedLabel(QString)), filtermodel, SLOT(removeLabel(QString)));
	connect(labellist, SIGNAL(addedBannedLabel(QString)), filtermodel, SLOT(addBannedLabel(QString)));
	connect(labellist, SIGNAL(removedBannedLabel(QString)), filtermodel, SLOT(removeBannedLabel(QString)));
	connect(labellist, SIGNAL(clearLabels()), filtermodel, SLOT(clearLabels()));
	connect(labellist, SIGNAL(clearBannedLabels()), filtermodel, SLOT(clearBannedLabels()));
}




