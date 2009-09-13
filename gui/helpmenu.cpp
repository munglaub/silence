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

#include "gui/helpmenu.h"

HelpMenu::HelpMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&Help"));
	about = addAction(QIcon(":/icons/actions/help-about.png"), tr("About"));
	connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));
}

HelpMenu::~HelpMenu()
{
	delete about;
}

void HelpMenu::showAbout()
{
	AboutDialog *dlg = new AboutDialog;
	dlg->exec();
	delete dlg;
}

