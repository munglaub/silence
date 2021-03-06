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

#include "src/data/model/listproxymodel.h"
#include "src/data/node/node.h"


Qt::ItemFlags ListProxyModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ListProxyModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
		return QVariant();

	Node *item = static_cast<Node*>(index.internalPointer());

	if (role == Qt::DecorationRole && item->getContent() != 0)
		return item->getContent()->getPixmap();

	if (item)
		return item->getCaption();

	return QVariant();
}

QModelIndex ListProxyModel::index(int row, int, const QModelIndex&) const
{
	return indexList[row];
}

QModelIndex ListProxyModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	return indexList[indexList.indexOf(index)].parent();
}

int ListProxyModel::rowCount(const QModelIndex&) const
{
	return indexList.size();
}

int ListProxyModel::columnCount(const QModelIndex&) const
{
	return 1;
}

QModelIndex ListProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return indexList[indexList.indexOf(sourceIndex)];
}

QModelIndex ListProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
	int index = indexList.indexOf(proxyIndex);
	if (index < indexList.count() && index >= 0)
		return indexList[index];
	return QModelIndex();
}

void ListProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
	QAbstractProxyModel::setSourceModel(sourceModel);
	update();
}

void ListProxyModel::update()
{
	QAbstractItemModel *sourceModel = QAbstractProxyModel::sourceModel();
	indexList.clear();
	// add all nodes to the list
	int column = 0;
	for (int row = 0; sourceModel->index(row, column).isValid(); row++)
	{
		QModelIndex aIndex = sourceModel->index(row, column);
		indexList.append(aIndex);
		addIndexes(&aIndex);
	}
}

void ListProxyModel::addIndexes(QModelIndex *searchIndex)
{
	int column = 0;
	for (int row = 0; searchIndex->child(row, column).isValid(); row++)
	{
	    QModelIndex aIndex = searchIndex->child(row, column);
	    indexList.append(aIndex);
	    addIndexes(&aIndex);
	}
}


