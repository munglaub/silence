#include "gui/aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("About Silence"));
        setWindowIcon(QIcon("icons/Silence_16px.png"));
        resize(330, 150);

        logo = new QLabel;
        logo->setPixmap(QPixmap("icons/Silence_big.png"));

        version = new QLabel(tr("Silence - very early Version"));
        authors = new QLabel(tr("Manuel Unglaub\nYves Adler\nMarcel Winkel"));
	
	quit = new QPushButton(tr("Close"));
	quit->setFixedWidth(100);
	connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

        subLayout = new QGridLayout();
        subLayout->setAlignment(Qt::AlignCenter);
        subLayout->addWidget(version, 1, 0, 1, 1, Qt::AlignTop);
        subLayout->addWidget(authors, 3, 0, 1, 1, Qt::AlignLeft);

	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
        layout->addWidget(logo, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addLayout(subLayout, 0, 1, 1, 1, Qt::AlignLeft);
        layout->addWidget(quit, 1, 0, 1, 2, Qt::AlignRight);
	setLayout(layout);
}

AboutDialog::~AboutDialog()
{
	delete quit;
	delete authors;
	delete version;
        delete logo;
        delete subLayout;
	delete layout;
}


