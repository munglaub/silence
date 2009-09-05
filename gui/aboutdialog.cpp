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

#include "gui/aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("About Silence"));
        setWindowIcon(QIcon("icons/Silence_16px.png"));
        resize(330, 150);

        logo = new QLabel;
        logo->setPixmap(QPixmap("icons/Silence_big.png"));

        version = new QLabel(tr("Silence - very early Version"));
        authors = new QLabel(tr("Manuel Unglaub\nYves Adler\nMarcel Winkel"));
	
	quit = new QPushButton(tr("Close"));
	quit->setFixedWidth(100);
	connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

        subLayout = new QGridLayout();
        subLayout->setAlignment(Qt::AlignCenter);
        subLayout->addWidget(version, 1, 0, 1, 1, Qt::AlignTop);
        subLayout->addWidget(authors, 3, 0, 1, 1, Qt::AlignLeft);

	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
        layout->addWidget(logo, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addLayout(subLayout, 0, 1, 1, 1, Qt::AlignLeft);
        layout->addWidget(quit, 1, 0, 1, 2, Qt::AlignRight);
	setLayout(layout);
}

AboutDialog::~AboutDialog()
{
	delete quit;
	delete authors;
	delete version;
        delete logo;
        delete subLayout;
	delete layout;
}


