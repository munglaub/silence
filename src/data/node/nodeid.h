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

#ifndef NODEID_H
#define NODEID_H

#include <QString>


/*!\class NodeId
 * \brief A id for the Node.
 *
 * The NodeId provides a id for the nodes. It can generate a unique id and provide this id in differtent types.
 *
 * \author Manuel Unglaub
 */
class NodeId
{
	public:
		/*!
		 * A constructor.
		 *
		 * Constructs the NodId and will generate a unique id.
		 */
		NodeId();

		/*! A constructor.
		 *
		 * Constructs the NodeId and will set the id.
		 * \param nodeid The id of theis NodeId.
		 */
		NodeId(int nodeid);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NodeId();

		/*!
		 *	Get the id of this NodeId as an int.
		 * \return The id of this NodeId.
		 */
		int getId() const;

		/*!
		 * Get the id of this NodeId as a QString.
		 * \return The id of this NodeId.
		 */
		QString toString();

		/*!
		 * Get the id of this NodeId as a QByteArray.
		 * \return The id of this NodeId.
		 */
		QByteArray toByteArray();

	private:
		void init(int nodeid);
		static int highestid;
		int id;
};

#endif // NODEID_H


