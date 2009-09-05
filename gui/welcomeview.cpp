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

#include "welcomeview.h"

WelcomeView* WelcomeView::welcomeview = 0;

WelcomeView::WelcomeView(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	int row = 0;

	icon = new QLabel;
	icon->setPixmap(QPixmap("icons/Silence_big.png"));
	layout->addWidget(icon, row, 0, 1, 2, Qt::AlignLeft);

	welcome = new QLabel(tr("Welcome to Silence, an information management tool."));
	welcome->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(welcome, row, 1, 1, 2, Qt::AlignLeft);
	++row;

	versionCap = new QLabel(tr("Version"));
	versionCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(versionCap, row, 0, 1, 1, Qt::AlignLeft);
	versionVal = new QLabel(tr("very early Version"));
	versionVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(versionVal, row, 1, 1, 1, Qt::AlignLeft);
	++row;

	authorCap = new QLabel(tr("Authors"));
	authorCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(authorCap, row, 0, 1, 1);
	authorVal = new QLabel(tr("Manuel Unglaub, Yves Adler, Marcel Winkel"));
	authorVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(authorVal, row, 1, 1, 1);
	++row;

	licenseCap = new QLabel(tr("License"));
	licenseCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(licenseCap, row, 0, 1, 1);
	licenseVal = new QLabel(tr("GPLv2"));
	licenseVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(licenseVal, row, 1, 1, 1);

	setLayout(layout);
}

WelcomeView* WelcomeView::create()
{
	if (welcomeview == 0)
		welcomeview = new WelcomeView;
	return welcomeview;
}

WelcomeView::~WelcomeView()
{
	delete licenseVal;
	delete licenseCap;
	delete authorVal;
	delete authorCap;
	delete versionVal;
	delete versionCap;
	delete welcome;
	delete icon;
	delete layout;
}


