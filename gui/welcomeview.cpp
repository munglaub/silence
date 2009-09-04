#include "welcomeview.h"

WelcomeView* WelcomeView::welcomeview = 0;

WelcomeView::WelcomeView(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	int row = 0;

	icon = new QLabel;
	icon->setPixmap(QPixmap("icons/Silence_big.png"));
	layout->addWidget(icon, row, 0, 1, 2, Qt::AlignLeft);
	++row;

	welcome = new QLabel(tr("Welcome to Silence, an information management tool."));
	welcome->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(welcome, row, 0, 1, 2, Qt::AlignLeft);
	++row;

	versionCap = new QLabel(tr("Version"));
	versionCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(versionCap, row, 0, 1, 1, Qt::AlignLeft);
	versionVal = new QLabel(tr("very early Version"));
	versionVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(versionVal, row, 1, 1, 1, Qt::AlignLeft);
	++row;

	authorCap = new QLabel(tr("Authors"));
	authorCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(authorCap, row, 0, 1, 1);
	authorVal = new QLabel(tr("Manuel Unglaub, Yves Adler, Marcel Winkel"));
	authorVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(authorVal, row, 1, 1, 1);
	++row;

	licenseCap = new QLabel(tr("License"));
	licenseCap->setFont(QFont("Times", 12, QFont::Bold));
	layout->addWidget(licenseCap, row, 0, 1, 1);
	licenseVal = new QLabel(tr("GPLv2"));
	licenseVal->setFont(QFont("Times", 12, QFont::Normal));
	layout->addWidget(licenseVal, row, 1, 1, 1);

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
	delete licenseVal;
	delete licenseCap;
	delete authorVal;
	delete authorCap;
	delete versionVal;
	delete versionCap;
	delete welcome;
	delete icon;
	delete layout;
}


