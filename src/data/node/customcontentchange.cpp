/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#include "src/data/node/customcontentchange.h"


CustomContentChange::CustomContentChange(QList<CustomNodeItem*> items, QStringList data, CustomContentView *view)
{
	this->view = view;
	this->items = items;
	this->data = data;
}

void CustomContentChange::updateContent()
{
	if (items.size() == data.size())
		for (int i = 0; i < items.size(); ++i)
			items.at(i)->setData(data.at(i));
}

void CustomContentChange::updateContentView()
{
	view->setData(data);
}


