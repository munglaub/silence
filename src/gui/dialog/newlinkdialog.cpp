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

#include "src/gui/dialog/newlinkdialog.h"

NewLinkDialog::NewLinkDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("New Link"));
	resize(300, 400);

	layout = new QGridLayout;
	int row = 0;

	lblLinkText = new QLabel(tr("Link Text"));
	layout->addWidget(lblLinkText, row, 0);
	ledLinkText = new KLineEdit;
	ledLinkText->setClearButtonShown(true);
	layout->addWidget(ledLinkText, row, 1);
	++row;

	tree = new QTreeView;
	model = new SimpleTreeModel;
	tree->setModel(model);
	layout->addWidget(tree, row, 0, 1, 2);
	++row;

	btnCancel = new QPushButton(tr("Cancel"));
	layout->addWidget(btnCancel, row, 0, 1, 1, Qt::AlignLeft);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
	btnOk = new QPushButton(tr("OK"));
	layout->addWidget(btnOk, row, 1, 1, 1, Qt::AlignRight);
	connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));

	setLayout(layout);
}

NewLinkDialog::~NewLinkDialog()
{
	delete ledLinkText;
	delete lblLinkText;
	delete btnOk;
	delete btnCancel;
	delete model;
	delete tree;
	delete layout;
}

void NewLinkDialog::setLinkText(QString text)
{
	ledLinkText->setText(text);
}

QString NewLinkDialog::getLinkText()
{
	return ledLinkText->text();
}

QUrl NewLinkDialog::getUrl()
{
	int id = model->getItem(tree->selectionModel()->currentIndex())->getId().getId();
	QUrl url("silence://0.0.0.0/" + QString::number(id));
	return url;
}



