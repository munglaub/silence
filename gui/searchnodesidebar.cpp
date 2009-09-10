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
#include "node/listproxymodel.h"
#include "gui/searchnodesidebar.h"

#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QRadioButton>

SearchNodeSidebar::SearchNodeSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
        : QDockWidget(title, parent, flags)
{
	// Setup the listproxy, which basically transforms the tree into a flat strcuture
	ListProxyModel *listProxy = new ListProxyModel;
	listProxy->setSourceModel(Controller::create()->getTreeView()->getTree()->model());

	// setup the filtermodel first, as everything else will connect to it
	filtermodel = new FilterModel;
	filtermodel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filtermodel->setSourceModel(listProxy);

	// setup the ui
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);

	// first row with input for plain text and expand button
	searchedit = new QLineEdit;
	layout->addWidget(searchedit, 0, 0);

	QPushButton *moreBtn = new QPushButton(QIcon("icons/arrow-up-double.png"), tr(""));
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 1);
	QPushButton *lessBtn = new QPushButton(QIcon("icons/arrow-down-double.png"), tr(""));
	lessBtn->setFlat(true);
	lessBtn->setMaximumWidth(30);
	lessBtn->hide();
	layout->addWidget(lessBtn, 0, 1);
	connect(moreBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), moreBtn, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), moreBtn , SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(hide()));

	// search options
	QGroupBox *optionbox = new QGroupBox(tr("Search Options"));
	QGridLayout *optboxlayout = new QGridLayout;
	optionbox->setLayout(optboxlayout);
	optionbox->setVisible(false);
	
	// search for caption/fulltext
	QRadioButton *captionBtn = new QRadioButton("Caption");
	captionBtn->setChecked(true);
	optboxlayout->addWidget(captionBtn, 0, 0);
	QRadioButton *fulltextBtn = new QRadioButton("Fulltext");
	optboxlayout->addWidget(fulltextBtn, 0, 1);
	connect(fulltextBtn, SIGNAL(toggled(bool)), filtermodel, SLOT(setFilterFulltextEnabled(bool)));
	connect(fulltextBtn, SIGNAL(toggled(bool)), filtermodel, SLOT(invalidate()));

	// search by contenttype
	QCheckBox *cbMime = new QCheckBox(tr("mime type"));
	optboxlayout->addWidget(cbMime, 1, 0, 1, 2);
	QComboBox *mimeCombo = new QComboBox;
	mimeCombo->addItem("text/plain");
	mimeCombo->addItem("text/richtext");
	mimeCombo->setEnabled(false);
	optboxlayout->addWidget(mimeCombo, 2, 0, 1, 2);
	connect(cbMime, SIGNAL(clicked(bool)), mimeCombo, SLOT(setEnabled(bool)));
	connect(cbMime, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterMimetypeEnabled(bool)));
	connect(cbMime, SIGNAL(clicked(bool)), filtermodel, SLOT(invalidate()));
	connect(mimeCombo, SIGNAL(currentIndexChanged(QString)), filtermodel, SLOT(setFilterMimetypeString(QString)));
	connect(mimeCombo, SIGNAL(currentIndexChanged(QString)), filtermodel, SLOT(invalidate()));

	// search by Date
	QFrame *datebox = new QFrame;
	QGridLayout *dateboxlayout = new QGridLayout;
	datebox->setLayout(dateboxlayout);
	dateboxlayout->setMargin(0);
	optboxlayout->addWidget(datebox, 3, 0, 1, 2);

	// creation date
	QCheckBox *cbCreated = new QCheckBox(tr("created between"));
	dateboxlayout->addWidget(cbCreated, 0, 0, 1, 3);
	QDateEdit *fromCreated = new QDateEdit(QDate::currentDate());
	fromCreated->setEnabled(false);
	dateboxlayout->addWidget(fromCreated, 1, 0);
	connect(cbCreated, SIGNAL(clicked(bool)), fromCreated, SLOT(setEnabled(bool)));
	connect(cbCreated, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterCreatedDateEnabled(bool)));
	connect(fromCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedFromDate(QDate)));
	connect(fromCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	QLabel *clbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(clbland, 1, 1);
	QDateEdit *toCreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(toCreated, 1, 2);
	toCreated->setEnabled(false);
	connect(cbCreated, SIGNAL(clicked(bool)), toCreated, SLOT(setEnabled(bool)));
	connect(toCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterCreatedToDate(QDate)));
	connect(toCreated, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	// modification date
	QCheckBox *cbModified = new QCheckBox(tr("modified between"));
	dateboxlayout->addWidget(cbModified, 2, 0, 1, 3);
	QDateEdit *fromModified = new QDateEdit(QDate::currentDate());
	fromModified->setEnabled(false);
	dateboxlayout->addWidget(fromModified, 3, 0);
	connect(cbModified, SIGNAL(clicked(bool)), fromModified, SLOT(setEnabled(bool)));
	connect(cbModified, SIGNAL(clicked(bool)), filtermodel, SLOT(setFilterModifiedDateEnabled(bool)));
	connect(fromModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedFromDate(QDate)));
	connect(fromModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	QLabel *mlbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(mlbland, 3, 1);
	QDateEdit *toModified = new QDateEdit(QDate::currentDate());
	toModified->setEnabled(false);
	dateboxlayout->addWidget(toModified, 3, 2);
	connect(cbModified, SIGNAL(clicked(bool)), toModified, SLOT(setEnabled(bool)));
	connect(toModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(setFilterModifiedToDate(QDate)));
	connect(toModified, SIGNAL(dateChanged(QDate)), filtermodel, SLOT(invalidate()));

	connect(moreBtn, SIGNAL(clicked(bool)), optionbox, SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), optionbox, SLOT(hide()));
	layout->addWidget(optionbox, 1, 0, 1, 2);

	results = new QListView;
	results->setModel(filtermodel);
	layout->addWidget(results, 2, 0, 1, 2);

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
