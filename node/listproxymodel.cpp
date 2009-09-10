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

#include "listproxymodel.h"
#include "node/node.h"

#include <iostream>

ListProxyModel::ListProxyModel(QObject * parent)
    : QAbstractProxyModel(parent)
{
	// TODO: remove if not needed
}


ListProxyModel::~ListProxyModel()
{
	// TODO: remove if not needed
}

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

	return "ERROR";
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
    return indexList[indexList.indexOf(proxyIndex)];
}


void ListProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
	QAbstractProxyModel::setSourceModel(sourceModel);
	
	indexList.clear();

	// Start searching in the model index
	for (int i = 0; sourceModel->index(i, 0).isValid(); i++)
	{
		QModelIndex aIndex = sourceModel->index(i, 0);
		indexList.append(aIndex);
		addIndexes(sourceModel, &aIndex);
	}
}

void ListProxyModel::addIndexes(const QAbstractItemModel *sourceModel,
			       QModelIndex *searchIndex)
{
	for (int i = 0; searchIndex->child(i, 0).isValid(); i++)
	{
	    QModelIndex aIndex = searchIndex->child(i, 0);
	    indexList.append(aIndex);
	    addIndexes(sourceModel, &aIndex);
	}
}


