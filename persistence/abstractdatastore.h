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

#include "data/label.h"
#include "data/node/node.h"
#include <QObject>


/*!\class AbstractDataStore
 * \brief An abstract class for the persistence backend.
 *
 * Implement this abstract class to create a persistence layer for this application. Which implementation of this class is used will be decided in the Controller.
 *
 * \author Manuel Unglaub
 */
class AbstractDataStore : public QObject
{
	Q_OBJECT

	public:
		/*!
		 * Get the node whose childs are the first level of nodes.
		 * \return The root of the nodes.
		 */
		virtual Node* getRootNode() = 0;

		/*!
		 * Get the root label of the hierarchical label structure.
		 * \return The root of the label structure.
		 */
		virtual Label* getRootLabel() = 0;

		/*!
		 * Remove a node with all its subnodes from the persistence layer.
		 * \param node The node which will be removed from the persistence layer.
		 */
		virtual void removeNode(Node *node) = 0;

		/*!
		 * Add a node to the persistence layer.
		 * \param node The node which will be added to the persistence layer.
		 */
		virtual void addNode(Node *node) = 0;

		/*!
		 * Add a label to the persistence layer.
		 * \param label The label wich will be added to the persistence layer.
		 */
		virtual void addLabel(Label *label) = 0;

		/*!
		 * Remove a label from the persistence layer.
		 * \param label The label which will be removed from the persistence layer.
		 */
		virtual void removeLabel(Label *label) = 0;

	public slots:
		/*!
		 * Save a node which has changed.
		 * \param node This node will be saved with all its changes.
		 */
		virtual void saveNode(Node *node) = 0;
};

#endif // ABSTRACTDATASTORE_H

