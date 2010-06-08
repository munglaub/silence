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
#include "src/gui/widget/searchnodeoptions.h"


SearchNodeOptions::SearchNodeOptions(QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	showOptions = false;

	title = new QLabel(i18n("Search Options"));
	layout->addWidget(title, 0, 0, 1, 1, Qt::AlignLeft);
	showBtn = new QPushButton(KIcon("arrow-down-double"), "");
	showBtn->setFlat(true);
	showBtn->setMaximumWidth(30);
	connect(showBtn, SIGNAL(clicked()), this, SLOT(toggleVisibility()));
	layout->addWidget(showBtn, 0, 1, 1, 1, Qt::AlignRight);
	layout->addWidget(createOptionbox(), 1, 0, 1, 2);

	setLayout(layout);
}

SearchNodeOptions::~SearchNodeOptions()
{
	delete mlbland;
	delete clbland;
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
	delete title;
	delete dateboxlayout;
	delete datebox;
	delete optboxlayout;
	delete optionbox;
	delete layout;
}

QWidget* SearchNodeOptions::createOptionbox()
{
	optionbox = new QGroupBox();
	optboxlayout = new QGridLayout;
	optionbox->setLayout(optboxlayout);
	optionbox->setVisible(false);
	
	// search for caption/fulltext
	captionBtn = new QRadioButton(i18nc("search by node caption", "Caption"));
	captionBtn->setChecked(true);
	optboxlayout->addWidget(captionBtn, 0, 0);
	fulltextBtn = new QRadioButton("Fulltext");
	connect(fulltextBtn, SIGNAL(toggled(bool)), this, SLOT(enableFulltext(bool)));
	optboxlayout->addWidget(fulltextBtn, 0, 1);

	// search by contenttype
	cbMime = new QCheckBox(i18n("mime type"));
	connect(cbMime, SIGNAL(clicked(bool)), this, SLOT(enableMimetype(bool)));
	optboxlayout->addWidget(cbMime, 1, 0, 1, 2);
	mimeCombo = new KComboBox;
	mimeCombo->addItem("text/plain");
	mimeCombo->addItem("text/richtext");
	mimeCombo->setEnabled(false);
	connect(mimeCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changedMimetype(QString)));
	optboxlayout->addWidget(mimeCombo, 2, 0, 1, 2);


	// search by Date
	datebox = new QFrame;
	dateboxlayout = new QGridLayout;
	datebox->setLayout(dateboxlayout);
	dateboxlayout->setMargin(0);
	optboxlayout->addWidget(datebox, 3, 0, 1, 2);

	// creation date
	cbCreated = new QCheckBox(i18n("created between"));
	connect(cbCreated, SIGNAL(clicked(bool)), this, SLOT(enableCreationDate(bool)));
	dateboxlayout->addWidget(cbCreated, 0, 0, 1, 3);

	fromCreated = new QDateEdit(QDate::currentDate());
	fromCreated->setEnabled(false);
	connect(fromCreated, SIGNAL(dateChanged(const QDate&)), this, SLOT(changeCreatedFrom(QDate)));
	dateboxlayout->addWidget(fromCreated, 1, 0);

	clbland = new QLabel(i18n("and"));
	dateboxlayout->addWidget(clbland, 1, 1);

	toCreated = new QDateEdit(QDate::currentDate());
	dateboxlayout->addWidget(toCreated, 1, 2);
	toCreated->setEnabled(false);
	connect(toCreated, SIGNAL(dateChanged(const QDate&)), this, SLOT(changeCreatedTo(QDate)));

	// modification date
	cbModified = new QCheckBox(i18n("modified between"));
	connect(cbModified, SIGNAL(clicked(bool)), this, SLOT(enableModificationDate(bool)));
	dateboxlayout->addWidget(cbModified, 2, 0, 1, 3);

	fromModified = new QDateEdit(QDate::currentDate());
	fromModified->setEnabled(false);
	connect(fromModified, SIGNAL(dateChanged(const QDate&)), this, SLOT(changeModifiedFrom(QDate)));
	dateboxlayout->addWidget(fromModified, 3, 0);

	mlbland = new QLabel(i18n("and"));
	dateboxlayout->addWidget(mlbland, 3, 1);

	toModified = new QDateEdit(QDate::currentDate());
	toModified->setEnabled(false);
	connect(toModified, SIGNAL(dateChanged(const QDate&)), this, SLOT(changeModifiedTo(QDate)));
	dateboxlayout->addWidget(toModified, 3, 2);

	return optionbox;
}

void SearchNodeOptions::toggleVisibility()
{
	if (showOptions)
	{
		showBtn->setIcon(KIcon("arrow-down-double"));
		showOptions = false;
	} else {
		showBtn->setIcon(KIcon("arrow-up-double"));
		showOptions = true;
	}
	optionbox->setVisible(showOptions);
}

void SearchNodeOptions::enableMimetype(bool enabled)
{
	mimeCombo->setEnabled(enabled);
	emit enabledMimetype(enabled);
}

void SearchNodeOptions::enableCreationDate(bool enabled)
{
	fromCreated->setEnabled(enabled);
	toCreated->setEnabled(enabled);
	emit changedCreatedFrom(fromCreated->date());
	emit changedCreatedTo(toCreated->date());
	emit enabledCreationDate(enabled);
}

void SearchNodeOptions::enableModificationDate(bool enabled)
{
	fromModified->setEnabled(enabled);
	toModified->setEnabled(enabled);
	emit changedModifiedFrom(fromModified->date());
	emit changedModifiedTo(toModified->date());
	emit enabledModificationDate(enabled);
}

void SearchNodeOptions::enableFulltext(bool enabled)
{
	emit enabledFulltext(enabled);
}

void SearchNodeOptions::changedMimetype(QString mimetype)
{
	emit mimetypeSelected(mimetype);
}

void SearchNodeOptions::changeCreatedFrom(QDate date)
{
	emit changedCreatedFrom(date);
}

void SearchNodeOptions::changeCreatedTo(QDate date)
{
	emit changedCreatedTo(date);
}

void SearchNodeOptions::changeModifiedFrom(QDate date)
{
	emit changedModifiedFrom(date);
}

void SearchNodeOptions::changeModifiedTo(QDate date)
{
	emit changedModifiedTo(date);
}




