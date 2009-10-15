/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
 *
 * This file is part of Silence.
 *
 * Silence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version GPLv2 only of the License.
 *
 * Silence is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "controller.h"
#include "gui/newnodedialog.h"
#include "node/richtextnodecontent.h"
#include "node/textnodecontent.h"
#include <QPushButton>
#include <QVBoxLayout>


NewNodeDialog::NewNodeDialog(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowTitle(tr("New Node"));
	resize(400, 400);

	baselayout = new QVBoxLayout;

	namelayout = new QFormLayout;
	nameedit = new QLineEdit(tr("Nodename"));
	nameedit->selectAll();
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

	synbox->addItem("Bash");
	synbox->addItem("Batch");
	synbox->addItem("CMake");
	synbox->addItem("C++");
	synbox->addItem("C#");
	synbox->addItem("CSS");
	synbox->addItem("D");
	synbox->addItem("Diff");
	synbox->addItem("HTML");
	synbox->addItem("IDL");
	synbox->addItem("Java");
	synbox->addItem("JavaScript");
	synbox->addItem("Lua");
	synbox->addItem("Makefile");
	synbox->addItem("Perl");
	synbox->addItem("POV");
	synbox->addItem("Python");
	synbox->addItem("Ruby");
	synbox->addItem("SQL");
	synbox->addItem("TeX");
	synbox->addItem("VHDL");

	typelayout->addWidget(synbox, 0, 3);
	baselayout->addLayout(typelayout);
	indexChanged(typebox->currentIndex());

	// Labels
	labelwidget = new LabelWidget;
	baselayout->addWidget(labelwidget);

	// buttons
	buttonlayout = new QGridLayout;
	cancel = new QPushButton(tr("Cancel"));
	buttonlayout->addWidget(cancel, 0, 0, 1, 1, Qt::AlignLeft);
	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
	ok = new QPushButton(tr("OK"));
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

	delete labelwidget;

	delete cancel;
	delete ok;
	delete buttonlayout;

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
	return labelwidget->getLabels();
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


