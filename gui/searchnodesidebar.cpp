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
#include "gui/searchnodesidebar.h"
#include "node/treemodel.h"


SearchNodeSidebar::SearchNodeSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(title, parent, flags)
{
	// Setup the listproxy, which basically transforms the tree into a flat strcuture
	listProxy = new ListProxyModel;
	listProxy->setSourceModel(Controller::create()->getTreeView()->getTree()->model());

	// setup the filtermodel first, as everything else will connect to it
	filtermodel = new FilterModel;
	filtermodel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filtermodel->setSourceModel(listProxy);

	// setup the ui
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);

	setupSearchRow();
	setupSearchOptions();
	setupSearchDate();

	connect(moreBtn, SIGNAL(clicked(bool)), optionbox, SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), optionbox, SLOT(hide()));
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
	delete lessBtn;
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

	moreBtn = new QPushButton(QIcon("icons/arrow-up-double.png"), "");
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 1);
	lessBtn = new QPushButton(QIcon("icons/arrow-down-double.png"), "");
	lessBtn->setFlat(true);
	lessBtn->setMaximumWidth(30);
	lessBtn->hide();
	layout->addWidget(lessBtn, 0, 1);
	connect(moreBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), moreBtn, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), moreBtn , SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(hide()));
}

void SearchNodeSidebar::setupSearchOptions()
{
	// search options
	optionbox = new QGroupBox(tr("Search Options"));
	optboxlayout = new QGridLayout;
	optionbox->setLayout(optboxlayout);
	optionbox->setVisible(false);
	
	// search for caption/fulltext
	captionBtn = new QRadioButton("Caption");
	captionBtn->setChecked(true);
	optboxlayout->addWidget(captionBtn, 0, 0);
	fulltextBtn = new QRadioButton("Fulltext");
	optboxlayout->addWidget(fulltextBtn, 0, 1);
	connect(fulltextBtn, SIGNAL(toggled(bool)), filtermodel, SLOT(setFilterFulltextEnabled(bool)));
	connect(fulltextBtn, SIGNAL(toggled(bool)), filtermodel, SLOT(invalidate()));

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
	connect(cbMime, SIGNAL(clicked(bool)), filtermodel, SLOT(invalidate()));
	connect(mimeCombo, SIGNAL(currentIndexChanged(QString)), filtermodel, SLOT(setFilterMimetypeString(QString)));
	connect(mimeCombo, SIGNAL(currentIndexChanged(QString)), filtermodel, SLOT(invalidate()));
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
	dateboxlayout->addWidget(cbCreated, 0, 0, 1, 3);
	fromCreated = new QDateEdit(QDate::currentDate());
	fromCreated->setEnabled(false);
	dateboxlayout->addWidget(fromCreated, 1, 0);
	connect(cbCreated, SIGNAL(clicked(bool)), fromCreated, SLOT(setEnabled(bool)));
	connect(cbCreated, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterCreatedDateEnabled(bool)));
	connect(fromCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedFromDate(QDate)));
	connect(fromCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	clbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(clbland, 1, 1);
	toCreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(toCreated, 1, 2);
	toCreated->setEnabled(false);
	connect(cbCreated, SIGNAL(clicked(bool)), toCreated, SLOT(setEnabled(bool)));
	connect(toCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedToDate(QDate)));
	connect(toCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	// modification date
	cbModified = new QCheckBox(tr("modified between"));
	dateboxlayout->addWidget(cbModified, 2, 0, 1, 3);
	fromModified = new QDateEdit(QDate::currentDate());
	fromModified->setEnabled(false);
	dateboxlayout->addWidget(fromModified, 3, 0);
	connect(cbModified, SIGNAL(clicked(bool)), fromModified, SLOT(setEnabled(bool)));
	connect(cbModified, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterModifiedDateEnabled(bool)));
	connect(fromModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedFromDate(QDate)));
	connect(fromModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	mlbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(mlbland, 3, 1);
	toModified = new QDateEdit(QDate::currentDate());
	toModified->setEnabled(false);
	dateboxlayout->addWidget(toModified, 3, 2);
	connect(cbModified, SIGNAL(clicked(bool)), toModified, SLOT(setEnabled(bool)));
	connect(toModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedToDate(QDate)));
	connect(toModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));
}



