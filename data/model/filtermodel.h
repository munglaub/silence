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

#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>


class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
	public:
		FilterModel(QObject *parent = 0);
		~FilterModel();

	public slots:
		void setFilterFixedString(const QString &pattern);

		void setFilterCreatedDateEnabled(bool enabled);
		void setFilterCreatedFromDate(const QDate &date); 
		void setFilterCreatedToDate(const QDate &date); 

		void setFilterModifiedDateEnabled(bool enabled);
		void setFilterModifiedFromDate(const QDate &date); 
		void setFilterModifiedToDate(const QDate &date); 

		void setFilterMimetypeEnabled(bool enabled);
		void setFilterMimetypeString(const QString &type);

		void setFilterFulltextEnabled(bool enabled);

	protected:
		virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

	private:
		bool	filterCreated,
				filterModified,
				filterMimetype,
				filterFulltext;
		QString *mimetype,
				searchString;
		QDateTime	*createdFromDate,
					*createdToDate,
					*modifiedFromDate,
					*modifiedToDate;
};

#endif // FILTERMODEL_H



