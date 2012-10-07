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

#include <QFile>
#include <QObject>
#include "src/data/node/node.h"


/*!\class KjotsImporter
 * \brief A class to import data from KJots.
 *
 * This class is able to import data from KJots which is available in the xml-based KJots book format. It creates Books for KJots-Books and RichTextNodes from KJots-Pages.
 *
 * \author Manuel Unglaub
 */
class KjotsImporter : public QObject
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the KjotsImporter.
		 *
		 * \param node The parent node to add the imported nodes.
		 * \param fileName The file to import.
		 */
		KjotsImporter(Node *node, QString fileName);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~KjotsImporter();

		/*!
		 * Import the Nodes from the file and add them to the parent node.
		 * \return A list of importet nodes. Contains the parent node because this node has to be saved to.
		 */
		QList<Node*> import();

	private:
		Node *rootNode;
		QString fileName;
		QList<Node*> importedNodes;

		void getBook(QDomElement element, Node *parentNode);
		void getPage(QDomElement element, Node *parentNode);
		QString readFile(QFile & file);

};

#endif // KJOTSIMPORTER_H

