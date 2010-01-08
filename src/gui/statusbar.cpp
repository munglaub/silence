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

#include "src/gui/statusbar.h"


StatusBar::StatusBar(QWidget *parent)
	: QStatusBar(parent)
{
	cursorPos = new QLabel("0 : 0");
	addWidget(cursorPos);
	saveStatus = new QLabel("");
	addWidget(saveStatus);
	nodeName = new QLabel("");
	addWidget(nodeName);
}

StatusBar::~StatusBar()
{
	delete nodeName;
	delete saveStatus;
	delete cursorPos;
}

void StatusBar::setNodeName(QString name)
{
	nodeName->setText(name);
}

void StatusBar::setSaveStatus(bool saved)
{
	if (saved)
		saveStatus->setText(tr("saved"));
	else
		saveStatus->setText(tr("changed"));
}

void StatusBar::setCursorPosition(int line, int col)
{
	QString text = QString::number(line) + " : " + QString::number(col);
	cursorPos->setText(text);
}

