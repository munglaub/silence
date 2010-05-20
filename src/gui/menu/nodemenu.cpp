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
#include "src/controller.h"
#include "src/gui/menu/nodemenu.h"


NodeMenu::NodeMenu(QWidget *parent)
	: QMenu(parent)
{
	Controller *controller = Controller::create();

	setTitle(i18n("&Node"));

	QList<QAction*> *actions = controller->getTreeView()->getNodeActions();
	for (int i=0; i<actions->size(); ++i)
		addAction(actions->at(i));
	delete actions;
}

