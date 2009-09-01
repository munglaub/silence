#ifndef NODEPROPERTYWIDGET_H
#define NODEPROPERTYWIDGET_H

#include "node/node.h"
#include <QComboBox>
#include <QDockWidget>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>


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
		QFormLayout *infolayout;
		QFrame *infoframe;
		QLineEdit *nodeName;
		QLabel *creationdate;
		QLabel *modificationdate;
		QComboBox *syntax;
		QPushButton *applyNodeInfo;

		// labeltab
		QGridLayout *labellayout;
		QFrame *labelframe;
		QLineEdit *newLabel;
		QPushButton *btnAddLabel;
		QListWidget *availlabels;
		QPushButton *applyLabels;

		QWidget* createNodeInfoTab();
		QWidget* createLabelTab();
	
};

#endif // NODEPROPERTYWIDGET_H

