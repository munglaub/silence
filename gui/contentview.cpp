#include "gui/contentview.h"
#include "gui/welcomeview.h"
#include <QLabel>
#include <QWidget>

ContentView::ContentView(QWidget *parent)
	: QWidget(parent)
{
	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	widget = WelcomeView::create();
	layout->addWidget(widget);
	setContent(NULL);
	setLayout(layout);
}

ContentView::~ContentView()
{
	delete layout;
}

void ContentView::setContent(AbstractNodeContent *content)
{
	layout->removeWidget(widget);
	widget->setVisible(false);
	if (!content){
		widget = WelcomeView::create();
	} else {
		widget = content->getWidget();
	}
	layout->addWidget(widget);
	widget->setVisible(true);
}

