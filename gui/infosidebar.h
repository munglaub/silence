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
		QLabel	*caption,
				*created,
				*createdDate,
				*lastedit,
				*lasteditDate,
				*labels,
				*labelsData,
				*metaInfo,
				*metaInfoData,
				*type,
				*typeName,
				*icon;

		// metainfos aus dem content
};

#endif // INFOSIDEBAR_H

