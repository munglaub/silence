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
#include "gui/sidebar/searchnodesidebar.h"
#include "data/model/treemodel.h"

SearchNodeSidebar::SearchNodeSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(title, parent, flags)
{
	// Setup the listproxy, which basically transforms the tree into a flat strcuture
	listProxy = new ListProxyModel;
	QAbstractItemModel *treemodel = Controller::create()->getTreeView()->getTree()->model();
	listProxy->setSourceModel(treemodel);
	// update the proxy when nodes are added or removed
	connect(treemodel, SIGNAL(rowsInserted(const QModelIndex&, int, int)), listProxy, SLOT(update()));
	connect(treemodel, SIGNAL(rowsRemoved(const QModelIndex&, int, int)), listProxy, SLOT(update()));

	// setup the filtermodel first, as everything else will connect to it
	filtermodel = new FilterModel;
	filtermodel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filtermodel->setSourceModel(listProxy);

	connect(this, SIGNAL(visibilityChanged(bool)), filtermodel, SLOT(invalidate()));

	// setup the ui
	showOptions = false;
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);

	setupSearchRow();
	setupSearchOptions();
	setupSearchDate();

	connect(moreBtn, SIGNAL(clicked()), this, SLOT(toggleOptionsVisibility()));
	layout->addWidget(optionbox, 1, 0, 1, 2);

	// setup the resultlist
	resultList = new QListView;
	resultList->setModel(filtermodel);
	layout->addWidget(resultList, 2, 0, 1, 2);

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
	delete moreBtn;
	delete searchedit;
	delete resultList;
	delete clbland;
	delete mlbland;
	delete mimeCombo;
	delete toModified;
	delete fromModified;
	delete toCreated;
	delete fromCreated;
	delete cbModified;
	delete cbCreated;
	delete cbMime;
	delete fulltextBtn;
	delete captionBtn;

	delete dateboxlayout;
	delete datebox;
	delete optboxlayout;
	delete optionbox;

	delete layout;
	delete frame;

	delete filtermodel;
	delete listProxy;
}

void SearchNodeSidebar::toggleOptionsVisibility()
{
	if (showOptions)
	{
		moreBtn->setIcon(QIcon(":/icons/actions/arrow-down-double.png"));
		showOptions = false;
	} else {
		moreBtn->setIcon(QIcon(":/icons/actions/arrow-up-double.png"));
		showOptions = true;
	}
	optionbox->setVisible(showOptions);
}

void SearchNodeSidebar::selectionChanged(QModelIndex current)
{
	QTreeView *tree = Controller::create()->getTreeView()->getTree();
	tree->selectionModel()->clearSelection();
	tree->selectionModel()->setCurrentIndex(filtermodel->mapToSource(current), QItemSelectionModel::Select);
	Controller::create()->getTreeView()->selectItem();
}

void SearchNodeSidebar::setupSearchRow()
{
	searchedit = new QLineEdit;
	layout->addWidget(searchedit, 0, 0);

	moreBtn = new QPushButton(QIcon(":/icons/actions/arrow-down-double.png"), "");
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 1);
}

void SearchNodeSidebar::setupSearchOptions()
{
	// search options
	optionbox = new QGroupBox(tr("Search Options"));
	optboxlayout = new QGridLayout;
	optionbox->setLayout(optboxlayout);
	optionbox->setVisible(false);
	
	// search for caption/fulltext
	captionBtn = new QRadioButton(tr("Caption"));
	captionBtn->setChecked(true);
	optboxlayout->addWidget(captionBtn, 0, 0);
	fulltextBtn = new QRadioButton("Fulltext");
	optboxlayout->addWidget(fulltextBtn, 0, 1);
	connect(fulltextBtn, SIGNAL(toggled(bool)), filtermodel, SLOT(setFilterFulltextEnabled(bool)));

	// search by contenttype
	cbMime = new QCheckBox(tr("mime type"));
	optboxlayout->addWidget(cbMime, 1, 0, 1, 2);
	mimeCombo = new QComboBox;
	mimeCombo->addItem("text/plain");
	mimeCombo->addItem("text/richtext");
	mimeCombo->setEnabled(false);
	optboxlayout->addWidget(mimeCombo, 2, 0, 1, 2);
	connect(cbMime, SIGNAL(clicked(bool)), mimeCombo, SLOT(setEnabled(bool)));
	connect(cbMime, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterMimetypeEnabled(bool)));
	connect(mimeCombo, SIGNAL(currentIndexChanged(QString)), filtermodel, SLOT(setFilterMimetypeString(QString)));
}

void SearchNodeSidebar::enableCreationDate(bool enabled)
{
	fromCreated->setEnabled(enabled);
	toCreated->setEnabled(enabled);
	if (enabled)
	{
		filtermodel->setFilterCreatedFromDate(toCreated->date());
		filtermodel->setFilterCreatedToDate(fromCreated->date());
	}
	filtermodel->setFilterCreatedDateEnabled(enabled);
}

void SearchNodeSidebar::enableModificationDate(bool enabled)
{
	fromModified->setEnabled(enabled);
	toModified->setEnabled(enabled);
	if (enabled)
	{
		filtermodel->setFilterModifiedFromDate(fromModified->date());
		filtermodel->setFilterModifiedToDate(toModified->date());
	}
	filtermodel->setFilterModifiedDateEnabled(enabled);
}

void SearchNodeSidebar::setupSearchDate()
{
	// search by Date
	datebox = new QFrame;
	dateboxlayout = new QGridLayout;
	datebox->setLayout(dateboxlayout);
	dateboxlayout->setMargin(0);
	optboxlayout->addWidget(datebox, 3, 0, 1, 2);

	// creation date
	cbCreated = new QCheckBox(tr("created between"));
	connect(cbCreated, SIGNAL(clicked(bool)), this, SLOT(enableCreationDate(bool)));
	dateboxlayout->addWidget(cbCreated, 0, 0, 1, 3);

	fromCreated = new QDateEdit(QDate::currentDate());
	fromCreated->setEnabled(false);
	dateboxlayout->addWidget(fromCreated, 1, 0);
	connect(fromCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedFromDate(QDate)));

	clbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(clbland, 1, 1);

	toCreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(toCreated, 1, 2);
	toCreated->setEnabled(false);
	connect(toCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedToDate(QDate)));

	// modification date
	cbModified = new QCheckBox(tr("modified between"));
	connect(cbModified, SIGNAL(clicked(bool)), this, SLOT(enableModificationDate(bool)));
	dateboxlayout->addWidget(cbModified, 2, 0, 1, 3);

	fromModified = new QDateEdit(QDate::currentDate());
	fromModified->setEnabled(false);
	dateboxlayout->addWidget(fromModified, 3, 0);
	connect(fromModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedFromDate(QDate)));

	mlbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(mlbland, 3, 1);

	toModified = new QDateEdit(QDate::currentDate());
	toModified->setEnabled(false);
	dateboxlayout->addWidget(toModified, 3, 2);
	connect(toModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedToDate(QDate)));
}



