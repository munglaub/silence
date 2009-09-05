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

#include "gui/searchnodedialog.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QRadioButton>


SearchNodeDialog::SearchNodeDialog(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowTitle(tr("Search Node"));
	resize(800, 500);
	QGridLayout *baseLayout = new QGridLayout;

	// Searchbox
	QGroupBox *searchbox = new QGroupBox;
	QGridLayout *searchboxlayout = new QGridLayout;
	QLabel *lblsearchtxt = new QLabel(tr("Find"));
	searchboxlayout->addWidget(lblsearchtxt, 0, 0);
	QLineEdit *searchedit = new QLineEdit;
	searchboxlayout->addWidget(searchedit, 0, 1);
	
	QRadioButton *captiononly = new QRadioButton(tr("caption only"));
	searchboxlayout->addWidget(captiononly, 1, 0);
	QRadioButton *fulltext = new QRadioButton(tr("fulltext"));
	searchboxlayout->addWidget(fulltext, 1, 1);
	searchbox->setLayout(searchboxlayout);
	baseLayout->addWidget(searchbox, 0, 0);

	// Search by Date
	QGroupBox *datebox = new QGroupBox(tr("Search by Date"));
	QGridLayout *dateboxlayout = new QGridLayout;
	QCheckBox *cbcreated = new QCheckBox(tr("created between"));
	dateboxlayout->addWidget(cbcreated, 0, 0);
	QDateEdit *fromcreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(fromcreated, 0, 1);
	QLabel *clbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(clbland, 0, 2);
	QDateEdit *tocreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(tocreated, 0, 3);

	QCheckBox *cbedited = new QCheckBox(tr("edited between"));
	dateboxlayout->addWidget(cbedited, 1, 0);
	QDateEdit *fromedited = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(fromedited, 1, 1);
	QLabel *elbland = new QLabel(tr("and"));
	dateboxlayout->addWidget(elbland, 1, 2);
	QDateEdit *toedited = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(toedited, 1, 3);

	datebox->setLayout(dateboxlayout);
	baseLayout->addWidget(datebox, 1, 0);

	// Nodetype
	QGroupBox *nodetypebox = new QGroupBox(tr("Nodetype"));
	QHBoxLayout *typeboxlayout = new QHBoxLayout;
	QComboBox *typebox = new QComboBox;
	typebox->addItem(tr("Text"));
	typebox->addItem(tr("Picture"));
	typebox->addItem(tr("whatever"));
	typeboxlayout->addWidget(typebox);
	nodetypebox->setLayout(typeboxlayout);
	baseLayout->addWidget(nodetypebox, 2, 0);

	// Tags
	QGroupBox *tagbox = new QGroupBox(tr("Tags"));
	QGridLayout *taglayout = new QGridLayout;
	QListView *availtags = new QListView;
	taglayout->addWidget(availtags, 0, 0, 2, 1);
	
	QPushButton *add = new QPushButton(tr(">"));
	taglayout->addWidget(add, 0, 1);
	QPushButton *rm = new QPushButton(tr("<"));
	taglayout->addWidget(rm, 1, 1);

	QListView *selectedtags = new QListView;
	taglayout->addWidget(selectedtags, 0, 2, 2, 1);
	tagbox->setLayout(taglayout);
	baseLayout->addWidget(tagbox, 0, 1, 3, 1);


	// Resultlabel
	QLabel *lblresult = new QLabel(tr("Results"));
	baseLayout->addWidget(lblresult, 3, 0);

	// Buttons
	QPushButton *close = new QPushButton(tr("Close"));
	baseLayout->addWidget(close, 3, 1, 1, 1, Qt::AlignLeft);
	QPushButton *search = new QPushButton(tr("Search"));
	baseLayout->addWidget(search, 3, 1, 1, 1, Qt::AlignRight);

	// Results
	QListView *results = new QListView;
	baseLayout->addWidget(results, 4, 0, 1, 2);


	setLayout(baseLayout);
}

SearchNodeDialog::~SearchNodeDialog()
{
}

