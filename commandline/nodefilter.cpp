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

#include "commandline/nodefilter.h"
#include <iostream>

using namespace std;


NodeFilter::NodeFilter(Node* root)
{
	nodes = root->toNodeList();
	nodes.removeOne(root);
	filterstring = QString("");
	fulltext = false;
	filterCreationDate = false;
	filterModificationDate = false;
	filterLabels = false;
	filterNolabels = false;
	filterMimetype = false;
}

NodeFilter::~NodeFilter()
{
	// TODO: remove if not used
}

void NodeFilter::setFilterString(QString filterstring)
{
	this->filterstring = filterstring;
}

void NodeFilter::enableFulltext(bool enabled)
{
	fulltext = enabled;
}

void NodeFilter::setCreationDateFilter(QDate from, QDate to)
{
	filterCreationDate = true;
	creationDateFrom = from;
	creationDateTo = to;
}

void NodeFilter::setModificationDateFilter(QDate from, QDate to)
{
	filterModificationDate = true;
	modificationDateFrom = from;
	modificationDateTo = to;
}

void NodeFilter::setLabelFilter(QStringList labels)
{
	filterLabels = true;
	this->labels = labels;
}

void NodeFilter::setNoLabelFilter(QStringList nolabels)
{
	filterNolabels = true;
	this->nolabels = nolabels;
}

void NodeFilter::setMimeTypFilter(QString mimetype)
{
	filterMimetype = true;
	this->mimetype = mimetype;
}

void NodeFilter::printNodes()
{
	filterNodes();
	cout << nodes.size() << " Results" << endl << endl;
	for (int i=0; i < nodes.size(); ++i)
	{
		cout << "(" << nodes.at(i)->getId().getId() << ") - ";
		cout << nodes.at(i)->getCaption().toStdString() << endl;
		cout << "  Created: " << nodes.at(i)->getCreationDate().toString(Qt::DefaultLocaleShortDate).toStdString();
		cout << ", Modified: " << nodes.at(i)->getModificationDate().toString(Qt::DefaultLocaleShortDate).toStdString() << endl;
		cout << "  Labels:  " << nodes.at(i)->getLabels()->join(", ").toStdString() << endl;
	}
}

void NodeFilter::filterNodes()
{
	Node *current = 0;
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		current = nodes.at(i);

		if (!current->getCaption().contains(filterstring, Qt::CaseInsensitive))
		{
			if (!current->getContent())
			{
				nodes.removeAt(i);
				continue;
			}
			if (!fulltext || !current->getContent()->contains(filterstring))
			{
				nodes.removeAt(i);
				continue;
			}
		}
		if (filterCreationDate)
		{
			if (current->getCreationDate().date() < creationDateFrom)
			{
				nodes.removeAt(i);
				continue;
			}
			if (current->getCreationDate().date() > creationDateTo)
			{
				nodes.removeAt(i);
				continue;
			}
		}
		if (filterModificationDate)
		{
			if (current->getModificationDate().date() < modificationDateFrom)
			{
				nodes.removeAt(i);
				continue;
			}
			if (current->getModificationDate().date() > modificationDateTo)
			{
				nodes.removeAt(i);
				continue;
			}
		}
		if (filterMimetype)
		{
			if (current->getContent()->getMimeType() != mimetype)
			{
				nodes.removeAt(i);
				continue;
			}
		}
		if (filterLabels)
		{
			if (!isSubset(current->getLabels(), &labels))
			{
				nodes.removeAt(i);
				continue;
			}
		}
		if (filterNolabels)
		{
			if (intersecting(current->getLabels(), &nolabels))
			{
				nodes.removeAt(i);
				continue;
			}
		}
	}
}

bool NodeFilter::intersecting(QStringList *a, QStringList *b)
{
	bool result = false;
	for (int i=0; i < a->size() && !result; ++i)
	{
		result = b->contains(a->at(i));
	}
	return result;
}

bool NodeFilter::isSubset(QStringList *set, QStringList *subset)
{
	bool result = true;
	for (int i=0; i < subset->size() && result; ++i)
	{
		result = set->contains(subset->at(i));
	}

	return result;
}


