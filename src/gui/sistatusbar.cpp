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

#include <klocalizedstring.h>
#include "src/gui/sistatusbar.h"


SiStatusBar::SiStatusBar(QWidget *parent)
	: KStatusBar(parent)
{
	cursorPos = new QLabel("0 : 0");
	addWidget(cursorPos);
	saveStatus = new QLabel("");
	addWidget(saveStatus);
	nodeName = new QLabel("");
	addWidget(nodeName);
}

SiStatusBar::~SiStatusBar()
{
	delete nodeName;
	delete saveStatus;
	delete cursorPos;
}

void SiStatusBar::setNodeName(QString name)
{
	nodeName->setText(name);
}

void SiStatusBar::setSaveStatus(bool saved)
{
	if (saved)
		saveStatus->setText(i18n("saved"));
	else
		saveStatus->setText(i18n("changed"));
}

void SiStatusBar::setCursorPosition(int line, int col)
{
	QString text = QString::number(line) + " : " + QString::number(col);
	cursorPos->setText(text);
}

