#include <QtGui>
 
#include "node/filtermodel.h"
#include "controller.h"

FilterModel::FilterModel(QObject *parent)
:QSortFilterProxyModel(parent) /* call superclass constructor */
{
	childAcceptsRow = false;
}

FilterModel::~FilterModel()
{
}


bool FilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	bool accepts = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent); /* call superclass method */
	
	return accepts;
}