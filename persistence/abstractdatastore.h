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

#ifndef ABSTRACTDATASTORE_H
#define ABSTRACTDATASTORE_H

#include "data/node/node.h"
#include "data/label.h"
#include <QObject>


class AbstractDataStore : public QObject
{
	Q_OBJECT

	public:
		virtual Node* getRootNode() = 0;
		virtual Label* getRootLabel() = 0;

		virtual void removeNode(Node *node) = 0;
		virtual void addNode(Node *node) = 0;

		virtual void addLabel(Label *label) = 0;
		virtual void removeLabel(Label *label) = 0;

	public slots:
		virtual void saveNode(Node *node) = 0;
};

#endif // ABSTRACTDATASTORE_H

