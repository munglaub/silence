#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include "node/abstractnodecontent.h"
#include <QVBoxLayout>
#include <QWidget>

class ContentView : public QWidget
{
	public:
		ContentView(QWidget *parent = 0);
		~ContentView();

		void setContent(AbstractNodeContent *content);
	private:
		QVBoxLayout *layout;
		QWidget *widget;
};

#endif // CONTENTVIEW_H


