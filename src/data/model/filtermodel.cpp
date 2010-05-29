/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
 * Copyright (C) 2009, 2010 Yves Adler <yves.adler@googlemail.com>
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

#include "src/controller.h"
#include "src/data/model/filtermodel.h"
#include "src/utils/listutils.h"


FilterModel::FilterModel(QObject *parent)
	:QSortFilterProxyModel(parent)
{
	filterCreated = false;
	createdFromDate = new QDateTime;
	createdToDate = new QDateTime;
	filterModified = false;
	modifiedFromDate = new QDateTime;
	modifiedToDate = new QDateTime;

	filterMimetype = false;
	mimetype = new QString("text/plain");

	filterFulltext = false;
}

FilterModel::~FilterModel()
{
	delete mimetype;
	delete createdFromDate;
	delete createdToDate;
	delete modifiedFromDate;
	delete modifiedToDate;
}

void FilterModel::setFilterFixedString(const QString &pattern)
{
	QSortFilterProxyModel::setFilterFixedString(pattern);
	searchString = QString(pattern);
	invalidate();
}

bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	QModelIndex source_index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent);
	Node *item = 0;
	if (source_index.isValid())
		item = static_cast<Node*>(source_index.internalPointer());
	
	bool accepts = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);

	if ((item) && (filterFulltext))
	{
		accepts = false; // caption search is invalid now!
		accepts = item->getContent()->contains(searchString);
	}

	if ((item) && (filterCreated))
	{
		if ((createdFromDate) && (item->getCreationDate().date() < createdFromDate->date()))
			accepts = false;
		
		if ((createdToDate) && (item->getCreationDate().date() > createdToDate->date()))
			accepts = false;
	}

	if ((item) && (filterModified))
	{
		if ((modifiedFromDate) && (item->getModificationDate().date() < modifiedFromDate->date()))
			accepts = false;
		
		if ((modifiedToDate) && (item->getModificationDate().date() > modifiedToDate->date()))
			accepts = false;
	}

	if ((item) && (filterMimetype))
	{
		if (item->getContent()->getMimeType().compare(*mimetype) != 0)
			accepts = false;
	}

	if ((item) && (!labels.isEmpty()))
	{
		if (! ListUtils::isSubset(item->getLabels(), &labels))
			accepts = false;
	}

	if ((item) && (!bannedLabels.isEmpty()))
	{
		if (ListUtils::intersecting(item->getLabels(), &bannedLabels))
			accepts = false;
	}
	return accepts;
}

void FilterModel::setFilterCreatedDateEnabled(bool enabled)
{
	filterCreated = enabled;
	invalidate();
}

void FilterModel::setFilterCreatedFromDate(const QDate &date)
{
	createdFromDate = new QDateTime(date);
	invalidate();
}

void FilterModel::setFilterCreatedToDate(const QDate &date)
{
	createdToDate = new QDateTime(date);
	invalidate();
}

void FilterModel::setFilterModifiedDateEnabled(bool enabled)
{
	filterModified = enabled;
	invalidate();
}

void FilterModel::setFilterModifiedFromDate(const QDate &date)
{
	modifiedFromDate = new QDateTime(date);
	invalidate();
}

void FilterModel::setFilterModifiedToDate(const QDate &date)
{
	modifiedToDate = new QDateTime(date);
	invalidate();
}

void FilterModel::setFilterMimetypeEnabled(bool enabled)
{
	filterMimetype = enabled;
	invalidate();
}

void FilterModel::setFilterMimetypeString(const QString &type)
{
	mimetype = new QString(type);
	invalidate();
}

void FilterModel::setFilterFulltextEnabled(bool enabled)
{
	filterFulltext = enabled;
	invalidate();
}

void FilterModel::addLabel(QString label)
{
	labels << label;
	invalidate();
}

void FilterModel::removeLabel(QString label)
{
	labels.removeOne(label);
	invalidate();
}

void FilterModel::clearLabels()
{
	bannedLabels.clear();
	invalidate();
}

void FilterModel::addBannedLabel(QString label)
{
	bannedLabels << label;
	invalidate();
}

void FilterModel::removeBannedLabel(QString label)
{
	bannedLabels.removeOne(label);
	invalidate();
}

void FilterModel::clearBannedLabels()
{
	bannedLabels.clear();
	invalidate();
}


