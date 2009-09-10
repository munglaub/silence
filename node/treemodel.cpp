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

#include <QtGui>

#include "node/node.h"
#include "node/treemodel.h"
#include "controller.h"

TreeModel::TreeModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootItem = Controller::create()->getDataStore()->getRoot();
}

TreeModel::~TreeModel()
{
	delete rootItem;
}

Node* TreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		Node *item = static_cast<Node*>(index.internalPointer());
		if (item) 
			return item;
	}
	return rootItem;
}

int TreeModel::columnCount(const QModelIndex&) const
{
	return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
		return QVariant();

	Node *item = getItem(index);
	if (role == Qt::DecorationRole && item->getContent() != 0)
		return item->getContent()->getPixmap();

	return item->getCaption();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
		return false;

	Node *item = getItem(index);
	bool result = item->setCaption(value.toString());
	if (result)
		emit dataChanged(index, index);

	return result;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}


QVariant TreeModel::headerData(int, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->getCaption();

	return QVariant();
}



QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
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

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	Node *parentItem = getItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->addChildren(position, rows);
	endInsertRows();

	return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	Node *parentItem = getItem(parent);
	bool success = true;
	
	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	Node *childItem = getItem(index);
	Node *parentItem = childItem->getParent();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->getIndex(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	Node *parentItem = getItem(parent);
	return parentItem->getChildCount();
}





