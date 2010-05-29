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

#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/data/model/simpletreemodel.h"


SimpleTreeModel::SimpleTreeModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootItem = Controller::create()->getDataStore()->getRootNode();
}

QVariant SimpleTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
//TODO:
	if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
		return QVariant();

	Node *item = getItem(index);
	if (role == Qt::DecorationRole && item->getContent() != 0)
		return item->getContent()->getPixmap();

	return item->getCaption();
}

Qt::ItemFlags SimpleTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SimpleTreeModel::headerData(int, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(i18n("Title"));

	return QVariant();
}

QModelIndex SimpleTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	Node *parentItem = getItem(parent);

	Node *childItem = parentItem->getChild(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex SimpleTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	Node *childItem = getItem(index);
	Node *parentItem = childItem->getParent();
	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->getIndex(), 0, parentItem);
}

int SimpleTreeModel::rowCount(const QModelIndex &parent) const
{
	Node *parentItem = getItem(parent);
	return parentItem->getChildCount();
}

int SimpleTreeModel::columnCount(const QModelIndex&) const
{
	return 1;
}

Node* SimpleTreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		Node *item = static_cast<Node*>(index.internalPointer());
		if (item) 
			return item;
	}
	return rootItem;
}




