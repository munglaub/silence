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


class ListProxyModel : public QAbstractProxyModel
{
	Q_OBJECT

    public:
		ListProxyModel (QObject * parent = 0);
		~ListProxyModel ();

		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant data(const QModelIndex &index, int role) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
		QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
		void setSourceModel(QAbstractItemModel *sourceModel);

	public slots:
		void update();

    private:
		void addIndexes(const QAbstractItemModel *sourceModel, QModelIndex *searchIndex);
		QList<QModelIndex> indexList;
};

#endif // LISTPROXYMODEL_H


