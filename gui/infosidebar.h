#ifndef INFOSIDEBAR_H
#define INFOSIDEBAR_H

#include "node/node.h"
#include <QDockWidget>
#include <QLabel>
#include <QGridLayout>


class InfoSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		InfoSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~InfoSidebar();

		void setData(Node *data);

	private slots:
		void updateInfos();

	private:
		Node *node; 

		QGridLayout *layout;
		QFrame *frame;

		// infos aus der node
		QLabel *caption;
		QLabel *icon;
		QLabel *created;
		QLabel *createdDate;
		QLabel *lastedit;
		QLabel *lasteditDate;
		QLabel *labels;
		QLabel *labelsData;
		QLabel *type;
		QLabel *typeName;

		// metainfos aus dem content
};

#endif // INFOSIDEBAR_H

