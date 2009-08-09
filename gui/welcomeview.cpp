#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include "welcomeview.h"

WelcomeView* WelcomeView::welcomeview = 0;

WelcomeView::WelcomeView(QWidget *parent)
	: QWidget(parent)
{
	QLabel *head = new QLabel(tr("Silence"));
	head->setFont(QFont("Times", 24, QFont::Bold));

	QLabel *welcome = new QLabel(tr("Welcome to Silence, an information management tool"));
	welcome->setFont(QFont("Times", 12, QFont::Bold));

	QLabel *versionCap = new QLabel(tr("Version"));
	versionCap->setFont(QFont("Times", 12, QFont::Bold));
	QLabel *versionVal = new QLabel(tr("very early Version"));
	versionVal->setFont(QFont("Times", 12, QFont::Normal));

	QLabel *authorCap = new QLabel(tr("Author"));
	authorCap->setFont(QFont("Times", 12, QFont::Bold));
	QLabel *authorVal = new QLabel(tr("Manuel Unglaub, Yves Adler"));
	authorVal->setFont(QFont("Times", 12, QFont::Normal));


	QLabel *todo = new QLabel(tr("TODO: find someone to fix this welcomeview!!!"));
	todo->setFont(QFont("Times", 16, QFont::Bold));

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(head, 0, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(welcome, 1, 0, 1, 2, Qt::AlignLeft);
	layout->addWidget(versionCap, 3, 0, 1, 1, Qt::AlignLeft);
	layout->addWidget(versionVal, 3, 1, 1, 1, Qt::AlignLeft);
	layout->addWidget(authorCap, 4, 0, 1, 1);
	layout->addWidget(authorVal, 4, 1, 1, 1);
	layout->addWidget(todo, 5, 0, 1, 2);

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


