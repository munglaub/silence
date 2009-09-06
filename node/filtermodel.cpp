/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler
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

#include "node/filtermodel.h"
#include "controller.h"

#include <QtGui>
#include <iostream>


FilterModel::FilterModel(QObject *parent)
:QSortFilterProxyModel(parent) /* call superclass constructor */
{
	filterCreated = false;
	createdFromDate = 0;
	createdToDate = 0; 
	filterModified = false;
	modifiedFromDate = 0;
	modifiedToDate = 0;
}

FilterModel::~FilterModel()
{
	// FIXME: remove this if not needed!
}


bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	bool accepts = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent); /* call superclass method */
// 	std::cout << source_row  << std::endl;


	QModelIndex source_index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent);
	if (!source_index.isValid()) // the column may not exist
	    return true;

	// auszug aus dem stringdings von superklasse:
// 	QString key = sourceModel()->data(source_index, this->filterRole()).toString();
// 	if (key.contains("DO"))
// 	  std::cout << "Foo" << std::endl;
// 	      return key.contains(d->filter_regexp);

	if (filterCreated)
	{
		// FIXME: put some life here
		return true;
	}

	return accepts;
}


void FilterModel::setFilterCreatedDateEnabled(bool enabled)
{
	filterCreated = enabled;
}


void FilterModel::setFilterCreatedFromDate(const QDate &date)
{
	createdFromDate = new QDate(date.year(), date.month(), date.day());
}


void FilterModel::setFilterCreatedToDate(const QDate &date)
{
	createdToDate = new QDate(date.year(), date.month(), date.day());
}


void FilterModel::setFilterModifiedDateEnabled(bool enabled)
{
	filterModified = enabled;
}


void FilterModel::setFilterModifiedFromDate(const QDate &date)
{
	modifiedFromDate = new QDate(date.year(), date.month(), date.day());
}


void FilterModel::setFilterModifiedToDate(const QDate &date)
{
	modifiedToDate = new QDate(date.year(), date.month(), date.day());
}