#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>


class StatusBar : public QStatusBar
{
	public:
		StatusBar(QWidget *parent = 0);
		~StatusBar();

		void setNodeName(QString name);

	private:
		QLabel *nodeName;
};

#endif // STATUSBAR_H



