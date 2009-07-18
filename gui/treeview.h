#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDockWidget>
#include <QTreeWidget>

class TreeView : public QDockWidget
{
        Q_OBJECT
        
	public:
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();
                
        private slots:
                void addTreeItem();
                void removeTreeItem();
                
        private:
                 QTreeWidget *tree;
};

#endif // TREEVIEW_H

