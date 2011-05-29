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
#include <QList>
#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/node.h"


/*!\class ChangeManager
 * \brief Handels unsaved changes of nodes.
 *
 * The ChangeManager contains a map of the unsaved nodes with their changes. New changes should be added and when changes are saved or dismissed thei should be removed.
 * This ChangeManagers createion and destruction should be handled by the Controller.
 *
 * \author Manuel Unglaub
 */
class ChangeManager : public QObject
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs this ChangeManager.
		 */
		ChangeManager();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~ChangeManager();

		/*!
		 * Add a unsaved Node with its Change.
		 * \param node The unsaved Node.
		 * \parem change The Change of the unsaved Node.
		 */
		void add(Node *node, AbstractContentChange *change);

		/*!
		 * Get a list of all unsaved nodes.
		 * \return A list of all unsaved nodes.
		 */
		QList<Node*> getNodes();

		/*!
		 * Save all the specified nodes.
		 * \param nodes The nodes which should be saved.
		 */
		void saveNodes(QList<Node*> nodes);

		/*!
		 * Find out if there are unsaved nodes.
		 * \return True if there are unsaved nodes.
		 */
		bool unsavedNodes();

	public slots:
		/*!
		 * Remove a Node with its change because it is saved or should not be saved.
		 * \param node The node which should be removed.
		 */
		void remove(Node *node);

	private:
		QHash<Node*, AbstractContentChange*> changes;
};

#endif // CHANGEMANAGER_H

