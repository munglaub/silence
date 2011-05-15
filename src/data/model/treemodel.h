/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "src/data/node/node.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


/*!\class TreeModel
 * \brief A tree model for the nodes.
 *
 * This model is a implementation of the QAbstractItemModel. For more information take a look at the QT documentation.
 *
 * The model is used by the TreeView.
 *
 * \author Manuel Unglaub
 */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the TreeModel which is a child of parent.
		 * \param parent The parent of this TreeModel.
		 */
		TreeModel(QObject *parent = 0);

		/*!
		 * Get the caption or icon, dependent on the role, of a Node specified by the index.
		 * \param index The index of the requested data.
		 * \param role The role of the requested data.
		 * \return The data stored under the given role for the item referred to by the index.
		 * \sa setData()
		 */
		QVariant data(const QModelIndex &index, int role) const;

		/*!
		 * Sets the role data for the item at index to value. The dataChanged() signal will be emitted if the data was successfully set.
		 *
		 * \param index The index of the Node.
		 * \param value The caption for the Node.
		 * \param role The role the data is for. Only Qt::EditRole will have any effect.
		 * \return True if successful.
		 * \sa data()
		 */
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		/*!
		 * Returns the item flags for the given index.
		 *
		 * \param index The index for the requested flags.
		 * \return If the index is valid a combination of the following flags: Qt::ItemIsEnabled, Qt::ItemIsSelectable, Qt::ItemIsEditable, Qt::ItemIsDragEnabled, Qt::ItemIsDropEnabled.
		 */
		Qt::ItemFlags flags(const QModelIndex &index) const;

		/*!
		 * Returns the date for the header.
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
		 * \sa columnCount()
		 */
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
	
		/*!
		 * Get the number of columns for the children of the given parent.
		 *
		 * \param parent The number of columns for the children under the given parent. (not used)
		 * \return The number of columns for the children of the given parent. Always 1 because there is only one column at the moment.
		 * \sa rowCount()
		 */
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		/*!
		 * Insert rows at a specified position to a given parent.
		 *
		 * \param position The position in the list of children of the parent.
		 * \param rows The number of rows to insert.
		 * \param parent The parent to insert the rows.
		 * \return True if successful.
		 * \sa removeRows()
		 */
		bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

		/*!
		 * Remove rows at a specified position from a given parent.
		 *
		 * \param position The position in th list of children of the parent.
		 * \param rows The number of rows to remove.
		 * \param parent The parent to remove the rows from.
		 * \return True if successful.
		 * \sa insertRows()
		 */
		bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

		/*!
		 * Find out which drop actions are supported by this model.
		 *
		 * \return The drop actions supported by this model.
		 */
		Qt::DropActions supportedDropActions() const;

		/*!
		 * Returns an object that contains serialized items of data corresponding to the list of indexes specified. The formats used to describe the encoded data is obtained from the mimeTypes() function.
		 *
		 * \param indexes The indexes that will be serialized.
		 * \return The object that contains serialized items of data.
		 */
		QMimeData* mimeData(const QModelIndexList &indexes) const;

		/*!
		 * Handles the data supplied by a drag and drop operation that ended with the given action.
		 *
		 * \param data The data supplied by a drag and drop operation.
		 * \param action The action the drag and drop operation ended with.
		 * \param row The row where the drag and drop operation ended.
		 * \param column The column where the drag and drop operation ended.
		 * \param parent The parent where the drag and drop operation ended.
		 * \return True if the dropping was successful.
		 */
		bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

		/*!
		 * Get a list of MIME types that can be used to describe a list of model indexes.
		 * This model supports the "application/silence-nodeid" mimetype.
		 *
		 * \return A list of MIME types that can be used to describe a list of model indexes.
		 */
		QStringList mimeTypes() const;

		/*!
		 * Get the node from a specified index.
		 *
		 * \param index The index of the requested Node.
		 * \return The node specified by the given index.
		 */
		Node* getItem(const QModelIndex &index) const;

		/*!
		 * Get the QModelIndex for a specified id.
		 * \param id The id of the node to look for.
		 * \return The QModelIndex of the node with the provided id.
		 */
		QModelIndex findByNodeId(int id);

	signals:
		/*!
		 * This signal will be emitted after a successful drop operation.
		 *
		 * \param index The index of the dropped node.
		 */
		void dropped(QModelIndex index);

	private:
		Node *rootItem;

		QModelIndex findByNodeId(int id, QModelIndex &searchindex);
};

#endif // TREEMODEL_H



