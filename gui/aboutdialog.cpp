#include "gui/aboutdialog.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("About Silence"));
	setFixedSize(350, 175);

	QLabel *head = new QLabel(tr("Silence"));
	head->setFont(QFont("Times", 18, QFont::Bold));

	QLabel *version = new QLabel(tr("very early Version"));
	version->setFont(QFont("Times", 12, QFont::Bold));

	QLabel *writtenby = new QLabel(tr("written by"));

	QLabel *author1 = new QLabel(tr("Manuel Unglaub"));
	author1->setFont(QFont("Times", 12, QFont::Bold));
	QLabel *author2 = new QLabel(tr("Yves Adler"));
	author2->setFont(QFont("Times", 12, QFont::Bold));
	
	QPushButton *quit = new QPushButton(tr("Close"));
	quit->setFixedWidth(100);
	connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(head, 0, 0, 1, 1, Qt::AlignRight);
	layout->addWidget(version, 0, 1, 1, 1, Qt::AlignLeft);
	layout->addWidget(writtenby, 1, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(author1, 2, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(author2, 3, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(quit, 4, 0, 1, 2, Qt::AlignRight);
	setLayout(layout);
}

AboutDialog::~AboutDialog()
{
}


