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

#ifndef LISTUTILS_H
#define LISTUTILS_H


#include <QStringList>


/*!\class ListUtils
 * \brief Utils for Lists.
 *
 * Some utils for lists.
 *
 * \author Manuel Unglaub
 */
class ListUtils
{
	public:
		/*!
		 * Determine if two lists are intersecting.
		 *
		 * \param a One of the two lists which will be analysed.
		 * \param b One of the two lists which will be analysed.
		 */
		static bool intersecting(const QStringList *a, const QStringList *b);

		/*!
		 * Determine if one list is a subset of the other.
		 *
		 * \param set Will be testet if it is a set of the subset.
		 * \param subset Will be testet if it is a subset of set.
		 */
		static bool isSubset(const QStringList *set, const QStringList *subset);
};

#endif // LISTUTILS_H

