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

#ifndef XMLDATASTORE_H
#define XMLDATASTORE_H

#include "src/data/label.h"
#include "src/data/node/node.h"
#include "src/persistence/abstractdatastore.h"
#include <QDomDocument>
#include <QObject>


/*!\class XmlDataStore
 * \brief A xml based persistence backend.
 *
 * This implementation of the AbstractDataStore can save the nodes and labels to a singel xml file.
 *
 * \author Manuel Unglaub
 */
class XmlDataStore : public AbstractDataStore
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the XmlDataStore.
		 */
		XmlDataStore();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~XmlDataStore();

		Node* getRootNode();
		Node *getNode(NodeId id);
		Label* getRootLabel();

		void removeNode(Node *node);
		void addNode(Node *node);

		void addLabel(Label *label);
		void removeLabel(Label *label);

	public slots:
		void saveNode(Node *node);
	
	private:
		Node *rootNode;
		Label *rootLabel;
		static const QString DATA_FILE;

		void saveAll();
		Node* findNode(Node* parent, NodeId id);

		void xmlToLabels(QDomElement &xmlLabels, Label* label);

		void addXmlNode(Node* node, QDomElement &parent, QDomDocument &doc);
		void xmlToNode(Node* parentNode, QDomNode &xmlNode, QDomDocument &doc);

		void writeLabels(QDomDocument &doc, QDomElement &parent, Label* parentLabel);
};

#endif // XMLDATASTORE_H

