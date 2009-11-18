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

#ifndef LABELMODEL_H
#define LABELMODEL_H

#include "data/label.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


/*!\class LabelModel
 * \brief A tree modle for the hierarchical Label structure.
 *
 * This model is a implementation of the QAbstractItemModel. For more information take a look at the QT documentation.
 *
 * \author Manuel Unglaub
 */
class LabelModel : public QAbstractItemModel
{
    Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the LabelModel which is a child of parent.
		 * \param parent The parent of this LabelModel.
		 */
		LabelModel(QObject *parent = 0);

		/*!
		 * Get the data of a Label specified by an index and a role.
		 *
		 * \param index The index of the requested data.
		 * \param role The role of the requested data.
		 * \return The data stored under the given role for the item referred to by the index.
		 * \sa setData()
		 */
		QVariant data(const QModelIndex &index, int role) const;

		/*!
		 * Get the item flags for the given index.
		 *
		 * \param index The index of the requested flags.
		 * \return If the index is valid a combination of the following flags: Qt::ItemIsEnabled, Qt::ItemIsSelectable.
		 */
		Qt::ItemFlags flags(const QModelIndex &index) const;

		/*!
		 * Returns the data for the header.
		 *
		 * \param section The section of the requested data.
		 * \param orientation The orientation of the requested data.
		 * \param role The role of the requested data.
		 * \return The header data.
		 */
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		/*!
		 * Get a specified index.
		 *
		 * \param row The row of the requested index.
		 * \param column The column of the requested index.
		 * \param parent The parent of the requested index.
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
		 * Get the number of children of a specified index.
		 *
		 * \param parent The index for the request of the number of its children.
		 * \return The number of rows under the given parent.
		 */
		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/*!
		 * Get the number of columns for the children of the given parent.
		 *
		 * \param parent The number of columns for the children under the given parent. (not used)
		 * \return The number of columns for the children of the given parent. Always 1 because there is only one column.
		 */
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		/*!
		 * Insert rows at a specified position to a given parent.
		 *
		 * \param position The position in the list of children of the parent.
		 * \param rows The number of rows to insert.
		 * \param parent The parent to insert the rows.
		 * \return True if successfull.
		 */
		bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

		/*!
		 * Sets the role data for the item at index to value.
		 *
		 * \param index The index of the Label.
		 * \param value The name of the Label.
		 * \param role The role the data is for. Only Qt:EditRole will have any effect.
		 * \return True if successfull.
		 * \sa data()
		 */
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		/*!
		 * Remove rows at a specified position from a given parent.
		 *
		 * \param position The position in th list of children of the parent.
		 * \param rows The number of rows to remove.
		 * \param parent The parent to remove the rows from.
		 * \return True if successfull.
		 * \sa insertRows()
		 */
		bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

		/*!
		 * Get the Label from a specified index.
		 *
		 * \param index The index of the requested Label.
		 * \return The Label specified by the given index.
		 */
		Label* getItem(const QModelIndex &index) const;


	private:
		Label *rootItem;

};

#endif // LABELMODEL_H



