#ifndef INFOSIDEBAR_H
#define INFOSIDEBAR_H

#include <QDockWidget>

class InfoSidebar : public QDockWidget
{
	public:
		InfoSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~InfoSidebar();
};

#endif // INFOSIDEBAR_H

