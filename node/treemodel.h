#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "node/node.h"


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
	QVariant headerData(int section, Qt::Orientation orientation,
						int role = Qt::DisplayRole) const;
    
	// a model must implement the index function
	QModelIndex index(int row, int column,
						const QModelIndex &parent = QModelIndex()) const;

	// get the model index of the parent of a given model index
	QModelIndex parent(const QModelIndex &index) const;
	
	// returns the number of childs of a given model index
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	
	// returns how many columns a given model index has
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	bool insertRows(int position, int rows, 
					const QModelIndex &parent = QModelIndex());

	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole);
	bool removeRows(int position, int rows,
					const QModelIndex &parent = QModelIndex());

	Node* getItem(const QModelIndex &index) const;


private:
    Node *rootItem;
};

#endif // TREMODEL_H



