/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <QObject>
#include "src/data/label.h"
#include "src/data/node/customnodetypedefinition.h"
#include "src/data/node/node.h"


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
		 * Get the node whose children are the first level of nodes.
		 * \return The root of the nodes.
		 */
		virtual Node* getRootNode() = 0;

		/*!
		 * Get a specific Node.
		 * \param id The id of the requested node.
		 * \return The node with the provided id or 0 if the node was not found.
		 */
		virtual Node* getNode(NodeId id) = 0;

		/*!
		 * Get the root label of the hierarchical label structure.
		 * \return The root of the label structure.
		 */
		virtual Label* getRootLabel() = 0;

		/*!
		 * Get a list with the names of all custom node types.
		 * \return A QStringList with the names of all custom node types.
		 */
		virtual QStringList getCustomNodeTypeNames() = 0;

		/*!
		 * Get a CustomNodeTypeDefinition by its name.
		 * \param name The name of the requested CustomNodeTypeDefinition.
		 * \return A CustomNodeTypeDefinition with the requested name. If it does not exists, a CustomNodeTypeDefinition with the specified name will be created, saved and returned.
		 */
		virtual CustomNodeTypeDefinition* getCustomNodeType(QString name) = 0;

		/*!
		 * Remove a CustomNodeTypeDefinition.
		 * \param typeName The name of the CustomNodeTypeDefinition which will be removed.
		 */
		virtual void removeCustomNodeType(QString typeName) = 0;

		/*!
		 * Save the CustomNodeTypeDefinition.
		 * \param type The CustomNodeTypeDefinition which will be saved.
		 */
		virtual void saveCustomNodeType(CustomNodeTypeDefinition *type) = 0;

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
		 * \param label The label which will be added to the persistence layer.
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

