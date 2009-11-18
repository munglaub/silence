/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub, Yves Adler
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

#ifndef LISTPROXYMODEL_H
#define LISTPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QItemSelection>
#include <QList>


/*!\classe ListProxyModel
 * \brief A proxy model from tree to list.
 *
 * This model is a implementation of the QAbstractProxyModel. For more information take a look at the QT documentation.
 *
 * \authors Manuel Unglaub, Yves Adler
 */
class ListProxyModel : public QAbstractProxyModel
{
	Q_OBJECT

    public:
		/*!
		 * Get the item flags fo the given index.
		 *
		 * \param index The index of the requested flags.
		 * \return If the index is valid a combination of the following flags: Qt::ItemIsEnabled, Qt::ItemIsSelectable.
		 */
		Qt::ItemFlags flags(const QModelIndex &index) const;

		/*!
		 * Get the data of a Node specified by an index and a role.
		 *
		 * \param index The index of the requested data.
		 * \param role The rolde of the requested data.
		 * \return The data stored under the given role for the item referred to by the index.
		 */
		QVariant data(const QModelIndex &index, int role) const;

		/*!
		 * Get a specified index.
		 *
		 * \param row The row of the requested index.
		 * \param column The column of the requested index (not used).
		 * \param parent The parent of the requested index (not used).
		 * \return The requested index.
		 */
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;


		/*!
		 * Get the parent of a specified index.
		 *
		 * \param index The child of the requested index.
		 * \return The parent index of the specified index.
		 */
		QModelIndex parent(const QModelIndex &index) const;

		/*!
		 * Get the number of rows. Because this is a flat list it is the number of nodes in that list.
		 *
		 * \param parent not used.
		 * \return The number of row.
		 */
		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/*!
		 * Get the number of columns.
		 *
		 * \param parent not used.
		 * \return Because there is only one column it will return 1.
		 */
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		/*!
		 * Get the model index in the proxy model that corresponds to the sourceIndex from the source model.
		 *
		 * \param sourceIndex The index from the source model.
		 * \return The index from the proxy model that corresponds to the sourceIndex.
		 * \sa mapToSource()
		 */
		QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

		/*!
		 * Get the model index in the source model that corresponds to the proxyIndex in the proxy model.
		 *
		 * \param proxyIndex The index from the proxy model.
		 * \return The index from the source model that corresponds to the proxyIndex.
		 * \sa mapFromSource()
		 */
		QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

		/*!
		 * Sets the given sourceModel to be processed by the proxy model.
		 *
		 * \param sourceModel The source model that will be processed by the proxy model.
		 */
		void setSourceModel(QAbstractItemModel *sourceModel);

	public slots:
		/*!
		 * Update the changes of the source model to the proxy model.
		 */
		void update();

    private:
		void addIndexes(QModelIndex *searchIndex);
		QList<QModelIndex> indexList;
};

#endif // LISTPROXYMODEL_H


