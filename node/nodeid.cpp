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

#include "node/nodeid.h"
#include <QString>

int NodeId::highestid = 0;

NodeId::NodeId()
{
	init(highestid + 1);
}

NodeId::NodeId(int nodeid)
{
	init(nodeid);
}

NodeId::~NodeId()
{
}

void NodeId::init(int nodeid)
{
	id = nodeid;
	if (id > highestid)
		highestid = id;
}

int NodeId::getId() const
{
	return id;
}

QString* NodeId::toString()
{
	QString *result = new QString;
	result->setNum(id);
	return result;
}

QByteArray NodeId::toByteArray()
{
	QByteArray result;
	result.setNum(id);
	return result;
}

