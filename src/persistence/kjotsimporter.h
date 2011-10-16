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

#ifndef KJOTSIMPORTER_H
#define KJOTSIMPORTER_H

#include <QObject>
#include "src/data/node/node.h"


//TODO: docu
class KjotsImporter : public QObject
{
	Q_OBJECT

	public:
		KjotsImporter(Node *node, QString fileName);
		~KjotsImporter();

		QList<Node*> import();

	private:
		Node *rootNode;
		QString fileName;
		QList<Node*> importedNodes;
};

#endif // KJOTSIMPORTER_H

