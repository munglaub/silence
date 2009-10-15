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

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "node/label.h"


class LabelModel : public QAbstractItemModel
{
    Q_OBJECT

	public:
		LabelModel(QObject *parent = 0);
		~LabelModel();

		QVariant data(const QModelIndex &index, int role) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
		Label* getItem(const QModelIndex &index) const;


	private:
		Label *rootItem;

};

#endif // LABELMODEL_H



