#include "gui/aboutdialog.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	QLabel *head = new QLabel(tr("Silence very early Version"));
	head->setFont(QFont("Times", 18, QFont::Bold));

	QLabel *writtenby = new QLabel(tr("written by"));
	writtenby->setAlignment(Qt::AlignCenter);


	QLabel *author1 = new QLabel(tr("Manuel Unglaub"));
	author1->setFont(QFont("Times", 12, QFont::Bold));
	author1->setAlignment(Qt::AlignCenter);
	QLabel *author2 = new QLabel(tr("Yves Adler"));
	author2->setFont(QFont("Times", 12, QFont::Bold));
	author2->setAlignment(Qt::AlignCenter);
	
	QPushButton *quit = new QPushButton(tr("Quit"));
	quit->setFixedWidth(100);
	connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

	layout = new QVBoxLayout();
	layout->addWidget(head);
	layout->addWidget(writtenby);
	layout->addWidget(author1);
	layout->addWidget(author2);
	layout->addWidget(quit);
	setLayout(layout);
}

AboutDialog::~AboutDialog()
{
	delete layout;
}


