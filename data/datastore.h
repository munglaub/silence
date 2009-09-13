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

#ifndef DATASTORE_H
#define DATASTORE_H

#include "node/node.h"
#include <QObject>
#include <QDomDocument>


class DataStore : public QObject
{
	Q_OBJECT

	public:
		DataStore();
		~DataStore();

		Node* getRoot();
		QStringList* getLabels();

		void remove(Node *node);
		void add(Node *node);

	public slots:
		void save(Node *node);
	
	private:
		Node *root;
		QStringList *labels;
		static const QString DATA_FILE;

		void xmlToLabels(QDomElement &xmlLabels);

		void addXmlNode(Node* node, QDomElement &parent, QDomDocument &doc);
		void xmlToNode(Node* parentNode, QDomNode &xmlNode, QDomDocument &doc);
};

#endif // DATASTORE_H

