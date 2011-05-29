/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/gui/changemanager.h"

ChangeManager::ChangeManager()
{
}

ChangeManager::~ChangeManager()
{
}


void ChangeManager::add(Node *node, AbstractContentChange *change)
{
	this->changes.insert(node, change);
}

QList<Node*> ChangeManager::getNodes()
{
	return this->changes.keys();
}

void ChangeManager::remove(Node *node)
{
	this->changes.remove(node);
}

void ChangeManager::saveNodes(QList<Node*> nodes)
{
	for (int i=0; i<nodes.size(); ++i)
		changes.value(nodes.at(i))->updateContent();
}

bool ChangeManager::unsavedNodes()
{
	return !this->changes.isEmpty();
}

