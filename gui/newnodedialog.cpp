#include "gui/newnodedialog.h"
#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>


NewNodeDialog::NewNodeDialog(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowTitle(tr("New Node"));
	resize(500, 250);

	QVBoxLayout *baselayout = new QVBoxLayout;

	QFormLayout *namelayout = new QFormLayout;
	QLineEdit *nameedit = new QLineEdit;
	namelayout->addRow(tr("Node name:"), nameedit);
	baselayout->addLayout(namelayout);

	// Type & highlighting
	QGridLayout *typelayout = new QGridLayout;
	QLabel *lbltype = new QLabel(tr("Type"));
	typelayout->addWidget(lbltype, 0, 0);
	QComboBox *typebox = new QComboBox;
	typebox->addItem(tr("Text"));
	typebox->addItem(tr("Picture"));
	typebox->addItem(tr("whatever"));
	typelayout->addWidget(typebox, 0, 1);

	QLabel *lblhighlight = new QLabel(tr("Syntax"));
	typelayout->addWidget(lblhighlight, 0, 2);
	QComboBox *synbox = new QComboBox;
	synbox->addItem(tr("none"));
	synbox->addItem(tr("C++"));
	synbox->addItem(tr("Java"));
	typelayout->addWidget(synbox, 0, 3);
	baselayout->addLayout(typelayout);

	// Tags
	QGroupBox *tagbox = new QGroupBox(tr("Tags"));
	QGridLayout *taglayout = new QGridLayout;
	QListView *availtags = new QListView;
	taglayout->addWidget(availtags, 0, 0, 2, 1);
	
	QPushButton *add = new QPushButton(tr(">"));
	taglayout->addWidget(add, 0, 1);
	QPushButton *rm = new QPushButton(tr("<"));
	taglayout->addWidget(rm, 1, 1);

	QListView *selectedtags = new QListView;
	taglayout->addWidget(selectedtags, 0, 2, 2, 1);
	tagbox->setLayout(taglayout);
	baselayout->addWidget(tagbox);

	// buttons
	QGridLayout *buttonlayout = new QGridLayout;
	QPushButton *cancel = new QPushButton(tr("Cancel"));
	buttonlayout->addWidget(cancel, 0, 0, 1, 1, Qt::AlignLeft);
	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
	QPushButton *ok = new QPushButton(tr("OK"));
	connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
	buttonlayout->addWidget(ok, 0, 1, 1, 1, Qt::AlignRight);
	baselayout->addLayout(buttonlayout);

	setLayout(baselayout);
}

NewNodeDialog::~NewNodeDialog()
{
}

