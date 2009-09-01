#ifndef NODEPROPERTYWIDGET_H
#define NODEPROPERTYWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include "node/node.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QListWidget>


class NodePropertyWidget : public QDockWidget
{
	Q_OBJECT
	
	public:
		NodePropertyWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~NodePropertyWidget();

		void setNode(Node *node);

	private slots:
		void saveNodeInfo();
		void saveLabels();
		void addLabel();

	private:
		Node *node;
		QVBoxLayout *layout;
		QFrame *frame;
		QTabWidget *tabwidget;

		// nodeinfotab
		QLineEdit *nodeName;
		QLabel *creationdate;
		QLabel *modificationdate;
		QComboBox *syntax;
		QPushButton *applyNodeInfo;

		// labeltab
		QGridLayout *labellayout;
		QLineEdit *newLabel;
		QPushButton *btnAddLabel;
		QListWidget *availlabels;
		QPushButton *applyLabels;

		QWidget* createNodeInfoTab();
		QWidget* createLabelTab();
		QWidget* createMetaInfoTab();
	
};

#endif // NODEPROPERTYWIDGET_H

