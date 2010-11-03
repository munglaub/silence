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

#include <kfiledialog.h>
#include <klocalizedstring.h>
#include "src/gui/dialog/newlinkdialog.h"


NewLinkDialog::NewLinkDialog(QWidget *parent)
	: QGridLayout(parent)
{
	int row = 0;

	lblLinkText = new QLabel(i18n("Link Text"));
	addWidget(lblLinkText, row, 0);
	ledLinkText = new KLineEdit;
	ledLinkText->setClearButtonShown(true);
	addWidget(ledLinkText, row, 1, 1, 2);
	++row;

	rbtnNode = new QRadioButton(i18n("Node"));
	rbtnNode->setChecked(true);
	addWidget(rbtnNode, row, 0, 1, 1, Qt::AlignTop);
	tree = new QTreeView;
	model = new SimpleTreeModel;
	tree->setModel(model);
	addWidget(tree, row, 1, 1, 2);
	connect(rbtnNode, SIGNAL(toggled(bool)), tree, SLOT(setEnabled(bool)));
	++row;

	rbtnWebUrl = new QRadioButton(i18n("Website Url"));
	addWidget(rbtnWebUrl, row, 0);
	ledWebUrl = new KLineEdit("http://");
	ledWebUrl->setClearButtonShown(true);
	ledWebUrl->setEnabled(false);
	addWidget(ledWebUrl, row, 1, 1, 2);
	connect(rbtnWebUrl, SIGNAL(toggled(bool)), ledWebUrl, SLOT(setEnabled(bool)));
	++row;

	rbtnFile = new QRadioButton(i18n("File"));
	addWidget(rbtnFile, row, 0);
	ledFile = new KLineEdit;
	ledFile->setClearButtonShown(true);
	ledFile->setEnabled(false);
	addWidget(ledFile, row, 1);
	connect(rbtnFile, SIGNAL(toggled(bool)), ledFile, SLOT(setEnabled(bool)));
	btnSelectFile = new QPushButton(i18n("Select File"));
	btnSelectFile->setEnabled(false);
	addWidget(btnSelectFile, row, 2);
	connect(rbtnFile, SIGNAL(toggled(bool)), btnSelectFile, SLOT(setEnabled(bool)));
	connect(btnSelectFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	++row;

	btnCancel = new QPushButton(i18n("Cancel"));
	btnCancel->setMinimumWidth(100);
	addWidget(btnCancel, row, 0, 1, 1, Qt::AlignLeft);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(exit()));
	btnOk = new QPushButton(i18n("OK"));
	btnOk->setMinimumWidth(100);
	addWidget(btnOk, row, 2, 1, 1, Qt::AlignRight);
	connect(btnOk, SIGNAL(clicked()), this, SLOT(addLink()));
}

NewLinkDialog::~NewLinkDialog()
{
	delete ledWebUrl;
	delete ledFile;
	delete ledLinkText;
	delete lblLinkText;
	delete rbtnNode;
	delete rbtnWebUrl;
	delete rbtnFile;
	delete btnSelectFile;
	delete btnOk;
	delete btnCancel;
	delete model;
	delete tree;
}

void NewLinkDialog::setLinkText(QString text)
{
	ledLinkText->setText(text);
}

QString NewLinkDialog::getLinkText()
{
	return ledLinkText->text();
}

KUrl NewLinkDialog::getUrl()
{
	KUrl url;
	if (rbtnNode->isChecked())
	{
		int id = model->getItem(tree->selectionModel()->currentIndex())->getId().getId();
		url = KUrl("silence://0.0.0.0/" + QString::number(id));
	}
	else if (rbtnWebUrl->isChecked())
	{
		url = KUrl(ledWebUrl->text());
	}
	else if (rbtnFile->isChecked())
	{
		url = KUrl(ledFile->text());
	}

	return url;
}

void NewLinkDialog::exit()
{
	delete this;
}

void NewLinkDialog::selectFile()
{
	QString fileName = KFileDialog::getOpenFileName(KUrl(), "*|" + i18n("All Files"), parentWidget(), i18n("Select File"));
	ledFile->setText(fileName);
}

void NewLinkDialog::addLink()
{
	QString linktext = getLinkText();
	QUrl url = getUrl();
	if (!url.isValid() || linktext.isEmpty())
		return;

	QString html = QString("<a href='%1'>%2</a>")
					.arg(url.toString())
					.arg(linktext);

	emit addedLink(html);
}


