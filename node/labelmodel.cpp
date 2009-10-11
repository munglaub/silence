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

#include "node/labelmodel.h"
#include "controller.h"


LabelModel::LabelModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootItem = Controller::create()->getDataStore()->getRootLabel();
}

LabelModel::~LabelModel()
{
	// TODO: foo
}

QVariant LabelModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	Label *item = getItem(index);
	return item->getText();
}

Qt::ItemFlags LabelModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant LabelModel::headerData(int, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->getText();
	return QVariant();
}

QModelIndex LabelModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	Label *parentItem = getItem(parent);

	Label *childItem = parentItem->getChild(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex LabelModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	Label *childItem = getItem(index);
	Label *parentItem = childItem->getParent();
	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->getIndex(), 0, parentItem);
}

int LabelModel::rowCount(const QModelIndex &parent) const
{
	Label *parentItem = getItem(parent);
	return parentItem->childCount();
}

int LabelModel::columnCount(const QModelIndex&) const
{
	return 1; // just one column
}

bool LabelModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	Label *parentItem = getItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->addChildren(position, rows);
	endInsertRows();

	return success;
}

bool LabelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::EditRole)
		return false;

	Label *label = getItem(index);
	label->setText(value.toString());
	return true;
}

bool LabelModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	Label *parentItem = getItem(parent);
	bool success = true;
	
	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}

Label* LabelModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		Label *item = static_cast<Label*>(index.internalPointer());
		if (item) 
			return item;
	}
	return rootItem;
}




