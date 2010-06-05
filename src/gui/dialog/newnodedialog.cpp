/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <klocalizedstring.h>
#include <QPushButton>
#include <QVBoxLayout>
#include "src/data/node/richtextnodecontent.h"
#include "src/data/node/textnodecontent.h"
#include "src/gui/dialog/newnodedialog.h"


NewNodeDialog::NewNodeDialog(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	setWindowTitle(i18n("New Node"));
	resize(400, 400);

	baselayout = new QVBoxLayout;

	namelayout = new QFormLayout;
	nameedit = new KLineEdit(i18n("Nodename"));
	nameedit->setClearButtonShown(true);
	nameedit->selectAll();
	namelayout->addRow(i18n("Node name:"), nameedit);
	baselayout->addLayout(namelayout);

	// Type & highlighting
	typelayout = new QGridLayout;
	lbltype = new QLabel(i18n("Type"));
	typelayout->addWidget(lbltype, 0, 0);
	typebox = new KComboBox;
	typebox->addItem(i18n("RichText"));
	typebox->addItem(i18n("Text"));
	connect(typebox, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
	typelayout->addWidget(typebox, 0, 1);

	syntaxbox = new SyntaxBox;
	typelayout->addWidget(syntaxbox, 0, 2, 1, 2);

	baselayout->addLayout(typelayout);

	indexChanged(typebox->currentIndex());

	// Labels
	labelwidget = new LabelWidget;
	baselayout->addWidget(labelwidget);

	// buttons
	buttonlayout = new QGridLayout;
	cancel = new QPushButton(i18n("Cancel"));
	buttonlayout->addWidget(cancel, 0, 0, 1, 1, Qt::AlignLeft);
	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
	ok = new QPushButton(i18n("OK"));
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
	delete syntaxbox;

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
			content->setSyntax(syntaxbox->getSyntax());
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
		syntaxbox->setEnabled(true);
	else
		syntaxbox->setEnabled(false);
}


