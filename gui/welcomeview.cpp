#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include "welcomeview.h"

WelcomeView* WelcomeView::welcomeview = 0;

WelcomeView::WelcomeView(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(new QLabel("Welcome"));
	setLayout(layout);
}

WelcomeView* WelcomeView::create()
{
	if (welcomeview == 0)
		welcomeview = new WelcomeView;
	return welcomeview;
}

WelcomeView::~WelcomeView()
{
}


