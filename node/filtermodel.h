#ifndef FILTERMODEL_H
#define FILTERMODEL_H
#include <QSortFilterProxyModel>

#include <QObject>

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
    public:
	FilterModel(QObject *parent = 0);
	~FilterModel();

    protected:
	virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
	
    private:
	bool childAcceptsRow;
};

#endif // FILTERMODEL_H



