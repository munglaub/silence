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

#include "src/utils/listutils.h"

bool ListUtils::intersecting(const QStringList *a, const QStringList *b)
{
	bool result = false;
	for (int i=0; i < a->size() && !result; ++i)
	{
		result = b->contains(a->at(i));
	}
	return result;
}

bool ListUtils::isSubset(const QStringList *set, const QStringList *subset)
{
	bool result = true;
	for (int i=0; i < subset->size() && result; ++i)
	{
		result = set->contains(subset->at(i));
	}

	return result;
}



