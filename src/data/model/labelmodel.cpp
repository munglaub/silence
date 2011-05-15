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
#include <QMimeData>
#include "src/controller.h"
#include "src/data/model/labelmodel.h"


LabelModel::LabelModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootItem = Controller::create()->getDataStore()->getRootLabel();
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
		return Qt::ItemIsDropEnabled;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant LabelModel::headerData(int, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(i18n("Label"));

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
	return 1;
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
	if (index.isValid()){
		Label *item = static_cast<Label*>(index.internalPointer());
		if (item) 
			return item;
	}
	return rootItem;
}

Qt::DropActions LabelModel::supportedDropActions() const
{
	return Qt::MoveAction | Qt::CopyAction;
}

QMimeData* LabelModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	// only on Label can be selected at a time
	Label *label = getItem(indexes.first());
	if (label)
		mimeData->setData("application/silence-label", QByteArray::number(label->getId()));
	return mimeData;
}

bool LabelModel::dropMimeData(const QMimeData *data, Qt::DropAction, int row, int, const QModelIndex & parent)
{
	int id = data->data("application/silence-label").toInt();
	QModelIndex movingIndex = findById(id);

	QModelIndex oldparent = movingIndex.parent();
	int oldPos = movingIndex.row();
	Label* oldparentLabel = getItem(oldparent);

	QModelIndex newparent = parent;
	if (newparent == movingIndex)
		return false;
	int newPos = row < 0 ? 0 : row;
	Label* newparentLabel = getItem(newparent);

	if (getItem(movingIndex)->contains(newparentLabel->getId()))
		return false;

	if (oldparent == newparent && oldPos < newPos)
		newPos -= 1;

	// move label
	if (oldPos < 0)
		oldPos = 0;
	beginRemoveRows(oldparent, oldPos, oldPos);
	Label *movingLabel = oldparentLabel->takeChild(oldPos);
	endRemoveRows();
	beginInsertRows(newparent, newPos, newPos);
	bool success = newparentLabel->addChild(newPos, movingLabel);
	endInsertRows();

	if (success)
		emit dropped(newparent.child(newPos, 0));

	return success;
}

QStringList LabelModel::mimeTypes() const
{
	QStringList types;
	types << "application/silence-label";
	return types;
}

QModelIndex LabelModel::findById(int id){
	int column = 0;
	for (int row = 0; index(row, column).isValid(); ++row){
		QModelIndex currentIndex = index(row, column);
		QModelIndex res = findById(id, currentIndex);
		if (res.isValid())
			return res;
	}
	return QModelIndex();
}


QModelIndex LabelModel::findById(int id, QModelIndex &searchIndex){
	if (getItem(searchIndex)->getId() == id)
		return searchIndex;
	int column = 0;
	for (int row = 0; searchIndex.child(row, column).isValid(); ++row){
		QModelIndex currentIndex = searchIndex.child(row, column);
		QModelIndex res = findById(id, currentIndex);
		if (res.isValid())
			return res;
	}
	return QModelIndex();
}





