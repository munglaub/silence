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

#include "src/controller.h"
#include "src/data/node/node.h"
#include "src/data/model/treemodel.h"
#include <QtGui>


TreeModel::TreeModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootItem = Controller::create()->getDataStore()->getRootNode();
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
	return 1;
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

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

Qt::DropActions TreeModel::supportedDropActions() const
{
	return Qt::MoveAction | Qt::CopyAction;
}

QVariant TreeModel::headerData(int, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(tr("Title"));

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

QModelIndex TreeModel::findByNodeId(int id)
{
	int column = 0;
	for (int row = 0; index(row, column).isValid(); ++row)
	{
		QModelIndex aIndex = index(row, column);
		QModelIndex res = findByNodeId(id, aIndex);
		if (res.isValid())
			return res;
	}
	return QModelIndex();
}

QModelIndex TreeModel::findByNodeId(int id, QModelIndex &searchindex)
{
	if (getItem(searchindex)->getId().getId() == id)
		return searchindex;
	int column = 0;
	for (int row = 0; searchindex.child(row, column).isValid(); ++row)
	{
		QModelIndex aIndex = searchindex.child(row, column);
		QModelIndex res = findByNodeId(id, aIndex);
		if (res.isValid())
			return res;
	}
	return QModelIndex();
}

bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction, int row, int, const QModelIndex & parent)
{
	// read nodeid from qmimedata and find node
	int id = data->data("application/silence-nodeid").toInt();
	QModelIndex movingIndex = findByNodeId(id);

	QModelIndex oldparent = movingIndex.parent();
	int oldPos = movingIndex.row();
	Node* oldparentNode = getItem(oldparent);

	QModelIndex newparent = parent;
	if (newparent == movingIndex)
		return false;
	int newPos = row < 0 ? 0 : row;
	Node* newparentNode = getItem(newparent);

	if (getItem(movingIndex)->contains(newparentNode))
		return false;

	if (oldparent == newparent && oldPos < newPos)
		newPos -= 1;

	// move node
	beginRemoveRows(oldparent, oldPos, oldPos);
	Node *movingNode = oldparentNode->takeChild(oldPos);
	endRemoveRows();
	beginInsertRows(newparent, newPos, newPos);
	bool success = newparentNode->addChild(movingNode, newPos);
	endInsertRows();

	if (success)
		emit dropped(newparent.child(newPos, 0));

	return success;
}

QStringList TreeModel::mimeTypes() const
{
	QStringList types;
	types << "application/silence-nodeid";
	return types;
}


QMimeData* TreeModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	// only one node can be selected at a time
	Node *node = getItem(indexes.first());
	if (node)
		mimeData->setData("application/silence-nodeid", node->getId().toByteArray());
	return mimeData;
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



