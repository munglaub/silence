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

#include "gui/silencemenu.h"
#include <QApplication>

SilenceMenu::SilenceMenu(QWidget *parent)
	: QMenu(parent)
{
	controller = Controller::create();

	setTitle(tr("&Silence"));

	QAction *preferences = addAction(tr("Preferences"));
	preferences->setEnabled(false);

	addSeparator();

	QAction *exit = addAction(tr("&Exit"));
	connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

SilenceMenu::~SilenceMenu()
{
}

