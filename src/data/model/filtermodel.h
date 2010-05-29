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

#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStringList>


/*!\class FilterModel
 * \brief A model to filter the nodes.
 *
 * This model is used to filter the nodes. It is a implementation of the QSortFilterProxyModel. For more information take a look at the QT documentation.
 *
 * \authors Yves Adler, Manuel Unglaub
 */
class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
	public:
		/*! The constructor.
		 *
		 * Constructs the FilterModel which is a child of parent.
		 * \param parent The parent of this FilterModel.
		 */
		FilterModel(QObject *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~FilterModel();

	public slots:
		/*!
		 * Sets the fixed string used to filter the contents of the source model to the given pattern.
		 *
		 * \param pattern Tha pattern to filter the contents of the source model.
		 */
		void setFilterFixedString(const QString &pattern);

		/*!
		 * Enable or disable filtering by creation date.
		 *
		 * \param enabled If true filter by creation date. Deactivate if false.
		 */
		void setFilterCreatedDateEnabled(bool enabled);

		/*!
		 * Set the from boundary of the creation date filter.
		 *
		 * \param date The from boundary of the creation date filter.
		 */
		void setFilterCreatedFromDate(const QDate &date); 

		/*!
		 * Set the to boundary of the creation date filter.
		 *
		 * \param date The to boundary of the creation date filter.
		 */
		void setFilterCreatedToDate(const QDate &date); 

		/*!
		 * Enable or disable filtering by modification date.
		 *
		 * \param enabled If true filter by modification date. Deactivate if false.
		 */
		void setFilterModifiedDateEnabled(bool enabled);

		/*!
		 * Set the from boundary of the modification date filter.
		 *
		 * \param date The from boundary of the modification date filter.
		 */
		void setFilterModifiedFromDate(const QDate &date); 

		/*!
		 * Set the to boundary of the modification date filter.
		 *
		 * \param date The to boundary of the modification date filter.
		 */
		void setFilterModifiedToDate(const QDate &date); 

		/*!
		 * Enable or disable filtering by MIME type.
		 *
		 * \param enabled If true filter by MIME type. Deactivate if false.
		 */
		void setFilterMimetypeEnabled(bool enabled);

		/*!
		 * Set the MIME type used to filter the contents of the source model.
		 *
		 * \param type The MIME type for the filtering.
		 */
		void setFilterMimetypeString(const QString &type);

		/*!
		 * Enable or disable the fulltext filtering.
		 *
		 * \param enabled If true use the whole content for the filtering. Deactivate if false.
		 */
		void setFilterFulltextEnabled(bool enabled);

		/*!
		 * Add a label to the filter. The node must contain all added labels to pass the filter.
		 *
		 * \param label This label will be added to this filter.
		 */
		void addLabel(QString label);

		/*!
		 * Remove a label from the filter. This label will no longer be relevant for the filter.
		 *
		 * \param label This label will be removed from this filter.
		 */
		void removeLabel(QString label);

		/*!
		 * Add a label to the filter. The node must not contain this label to pass the filter.
		 *
		 * \param label This label will be added to the filter.
		 */
		void addBannedLabel(QString label);

		/*!
		 * Remove all labels from this filter.
		 */
		void clearLabels();

		/*!
		 * Remove a label form the filter. This label will no longer be relevant for the filter.
		 *
		 * \param label This label will be removed from this filter.
		 */
		void removeBannedLabel(QString label);

		/*!
		 * Remove all banned labels from this filter.
		 */
		void clearBannedLabels();

	protected:
		/*!
		 * Returns true if the item in the row indicated by the given source_row and source_parent should be included in the model; otherwise returns false.
		 *
		 * \param source_row The source row.
		 * \param source_parent The source parent index.
		 * \return true if the item in the row indicated by the given source_row and source_parent should be indclude in the model.
		 */
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
		QStringList labels,
					bannedLabels;
};

#endif // FILTERMODEL_H



