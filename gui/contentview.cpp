#include "gui/contentview.h"
#include "gui/welcomeview.h"
#include <QLabel>
#include <QWidget>

ContentView::ContentView(QWidget *parent)
	: QWidget(parent)
{
	layout = new QVBoxLayout;
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
	widget->setHidden(true);
	if (!content){
		widget = WelcomeView::create();
	} else {
		widget = content->getWidget();
	}
	layout->addWidget(widget);
	widget->setHidden(false);
}

