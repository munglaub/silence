#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>


class StatusBar : public QStatusBar
{
	Q_OBJECT

	public:
		StatusBar(QWidget *parent = 0);
		~StatusBar();

		void setNodeName(QString name);
	
	public slots:
		void setCursorPosition(int line, int col);

	private:
		QLabel	*nodeName,
				*cursorPos;
};

#endif // STATUSBAR_H



