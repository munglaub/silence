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

#ifndef CHANGEMANAGER_H
#define CHANGEMANAGER_H

#include <QHash>
#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/node.h"
#include <QList>


//TODO: docu
class ChangeManager : public QObject
{
	Q_OBJECT

	public:
		ChangeManager();
		~ChangeManager();

		void add(Node *node, AbstractContentChange *change);
		QList<Node*> getNodes();
		void saveNodes(QList<Node*> nodes);
		bool unsavedNodes();

	public slots:
		void remove(Node *node);

	private:
		QHash<Node*, AbstractContentChange*> changes;
};

#endif // CHANGEMANAGER_H

