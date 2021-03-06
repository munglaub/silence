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

#include "src/data/node/customnodetypedefinition.h"


CustomNodeTypeDefinition::CustomNodeTypeDefinition(QString name)
{
	this->name = name;
}

CustomNodeTypeDefinition::~CustomNodeTypeDefinition()
{
	while (!itemList.isEmpty())
		delete itemList.takeFirst();
}

QString CustomNodeTypeDefinition::getName() const
{
	return name;
}

QList<CustomNodeItem*> CustomNodeTypeDefinition::getItemList() const
{
	return itemList;
}

void CustomNodeTypeDefinition::addItem(CustomNodeItem *item)
{
	itemList.append(item);
}

void CustomNodeTypeDefinition::removeItem(CustomNodeItem *item)
{
	itemList.removeOne(item);
}


