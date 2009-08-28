#include "gui/newnodedialog.h"
#include "node/richtextnodecontent.h"
#include "node/textnodecontent.h"
#include <QDialog>
#include <QGroupBox>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>


NewNodeDialog::NewNodeDialog(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowTitle(tr("New Node"));
	resize(500, 250);

	baselayout = new QVBoxLayout;

	namelayout = new QFormLayout;
	nameedit = new QLineEdit("Nodename");
	namelayout->addRow(tr("Node name:"), nameedit);
	baselayout->addLayout(namelayout);



	// Type & highlighting
	typelayout = new QGridLayout;
	lbltype = new QLabel(tr("Type"));
	typelayout->addWidget(lbltype, 0, 0);
	typebox = new QComboBox;
	typebox->addItem(tr("RichText"));
	typebox->addItem(tr("Text"));
	connect(typebox, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
	typelayout->addWidget(typebox, 0, 1);

	lblhighlight = new QLabel(tr("Syntax"));
	typelayout->addWidget(lblhighlight, 0, 2);
	synbox = new QComboBox;
	synbox->addItem(tr("None"));

	synbox->addItem(tr("Bash"));
	synbox->addItem(tr("Batch"));
	synbox->addItem(tr("CMake"));
	synbox->addItem(tr("C++"));
	synbox->addItem(tr("C#"));
	synbox->addItem(tr("CSS"));
	synbox->addItem(tr("D"));
	synbox->addItem(tr("Diff"));
	synbox->addItem(tr("HTML"));
	synbox->addItem(tr("IDL"));
	synbox->addItem(tr("Java"));
	synbox->addItem(tr("JavaScript"));
	synbox->addItem(tr("Lua"));
	synbox->addItem(tr("Makefile"));
	synbox->addItem(tr("Perl"));
	synbox->addItem(tr("POV"));
	synbox->addItem(tr("Python"));
	synbox->addItem(tr("Ruby"));
	synbox->addItem(tr("SQL"));
	synbox->addItem(tr("TeX"));
	synbox->addItem(tr("VHDL"));

	typelayout->addWidget(synbox, 0, 3);
	baselayout->addLayout(typelayout);
	indexChanged(typebox->currentIndex());

	// Tags
	QGroupBox *tagbox = new QGroupBox(tr("Tags"));
	tagbox->setEnabled(false);
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
	ok->setDefault(true);
	connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
	buttonlayout->addWidget(ok, 0, 1, 1, 1, Qt::AlignRight);
	baselayout->addLayout(buttonlayout);

	setLayout(baselayout);
}

NewNodeDialog::~NewNodeDialog()
{
	delete nameedit;
	delete namelayout;

	delete lbltype;
	delete typebox;
	delete typelayout;
	delete lblhighlight;
	delete synbox;

	delete baselayout;
}

QString NewNodeDialog::getCaption() const
{
	return nameedit->text();
}

AbstractNodeContent* NewNodeDialog::getContent() const
{
	switch (typebox->currentIndex())
	{
		case 0:
			return new RichTextNodeContent;
			break;
		case 1:
			TextNodeContent *content;
			content = new TextNodeContent;
			content->setSyntax(synbox->currentText());
			return content;
			break;
		default:
			return new RichTextNodeContent;
			break;
	}
}

QStringList NewNodeDialog::getLabels() const
{
	//TODO: real implementation
	QStringList result;
	result << "Foo" << "Foobar" << "Bar";
	return result;
}

void NewNodeDialog::indexChanged(int index)
{
	if (index == 1)
	{
		lblhighlight->setEnabled(true);
		synbox->setEnabled(true);
	} else {
		lblhighlight->setEnabled(false);
		synbox->setEnabled(false);
	}
}


