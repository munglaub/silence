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

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "data/node/node.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

	public:
		TreeModel(QObject *parent = 0);
		~TreeModel();

		// fuer die caption
		QVariant data(const QModelIndex &index, int role) const;

		// make sure the model has the right setup
		Qt::ItemFlags flags(const QModelIndex &index) const;

		// get the data stored in the nodes
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    
		// a model must implement the index function
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

		// get the model index of the parent of a given model index
		QModelIndex parent(const QModelIndex &index) const;
	
		// returns the number of childs of a given model index
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
	
		// returns how many columns a given model index has
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
		Node* getItem(const QModelIndex &index) const;

		Qt::DropActions supportedDropActions() const;
		QMimeData* mimeData(const QModelIndexList &indexes) const;
		bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex & parent);
		QStringList mimeTypes() const;

	signals:
		void dropped(QModelIndex index);

	private:
		Node *rootItem;

		QModelIndex findByNodeId(int id);
		QModelIndex findByNodeId(int id, QModelIndex &searchindex);
};

#endif // TREEMODEL_H



