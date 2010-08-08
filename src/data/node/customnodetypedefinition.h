/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#ifndef CUSTOMNODETYPEDEFINITION_H
#define CUSTOMNODETYPEDEFINITION_H

#include <QList>
#include <QString>
#include "src/data/node/customnodeitem.h"


/*!\class CustomNodeTypeDefinition
 * \brief Defines a custom node type.
 *
 * Contains a list of CustomNodeItems and the name of this type.
 *
 * \author Manuel Unglaub
 */
class CustomNodeTypeDefinition
{
	public:
		/*! The constructor.
		 *
		 * Constructs the CustomNodeTypeDefinition.
		 * \param name The name of this type.
		 */
		CustomNodeTypeDefinition(QString name);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~CustomNodeTypeDefinition();

		/*!
		 * Get the name of this CustomNodeTypeDefinition.
		 * \return The name of this type.
		 */
		QString getName() const;

		/*!
		 * Get a list of the CustomNodeItems contained in this CustomNodeTypeDefinition.
		 * \return The list of CustomNodeItems contained in this type.
		 */
		QList<CustomNodeItem*> getItemList() const;

		/*!
		 * Add a CustomNodeItem to this CustomNodeTypeDefinition.
		 * \param item This CustomNodeItem will be added to this type.
		 */
		void addItem(CustomNodeItem *item);

		/*!
		 * Remove a CustomNodeItem form this CustomNodeTypeDefinition.
		 * \param item The CustomNodeItem which will be removed from this type.
		 */
		void removeItem(CustomNodeItem *item);

	private:
		QString name;
		QList<CustomNodeItem*> itemList;
};

#endif // CUSTOMNODETYPEDEFINITION_H

