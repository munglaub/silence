#include "gui/aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("About Silence"));
	resize(350, 200);

	head = new QLabel(tr("Silence"));
	head->setFont(QFont("Times", 18, QFont::Bold));

	version = new QLabel(tr("very early Version"));
	version->setFont(QFont("Times", 12, QFont::Bold));

	writtenby = new QLabel(tr("written by"));

	authors = new QLabel(tr("Manuel Unglaub\nYves Adler\nMarcel Winkel"));
	authors->setFont(QFont("Times", 12, QFont::Bold));
	
	quit = new QPushButton(tr("Close"));
	quit->setFixedWidth(100);
	connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(head, 0, 0, 1, 1, Qt::AlignRight);
	layout->addWidget(version, 0, 1, 1, 1, Qt::AlignLeft);
	layout->addWidget(writtenby, 1, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(authors, 2, 0, 1, 2, Qt::AlignCenter);
	layout->addWidget(quit, 3, 0, 1, 2, Qt::AlignRight);
	setLayout(layout);
}

AboutDialog::~AboutDialog()
{
	delete quit;
	delete authors;
	delete writtenby;
	delete version;
	delete head;
	delete layout;
}


