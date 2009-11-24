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

#ifndef NODEFILTER_H
#define NODEFILTER_H

#include <QString>
#include <QStringList>
#include <QDate>
#include "data/node/node.h"


class NodeFilter
{
	public:
		NodeFilter(Node* root);
		~NodeFilter();
		
		void setFilterString(QString filterstring);
		void enableFulltext(bool enabled);
		void setCreationDateFilter(QDate from, QDate to);
		void setModificationDateFilter(QDate from, QDate to);
		void setLabelFilter(QStringList labels);
		void setNoLabelFilter(QStringList nolabels);
		void setMimeTypFilter(QString mimetype);

		void printNodes();
	private:
		QList<Node*> nodes;
		bool	fulltext,
				filterCreationDate,
				filterModificationDate,
				filterLabels,
				filterNolabels,
				filterMimetype;

		QString filterstring,
				mimetype;
		QDate	creationDateFrom,
				creationDateTo,
				modificationDateFrom,
				modificationDateTo;
		QStringList labels,
					nolabels;

		void filterNodes();
		bool intersecting(QStringList *a, QStringList *b);
		bool isSubset(QStringList *set, QStringList *subset);
};

#endif // NODEFILTER_H



