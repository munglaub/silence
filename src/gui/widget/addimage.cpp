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
#include "src/gui/widget/addimage.h"


AddImage::AddImage(QWidget *parent)
{
	this->parent = parent;
	setAlignment(Qt::AlignLeft);
	int row = 0;

	ledFile = new KLineEdit;
	ledFile->setClearButtonShown(true);
	addWidget(ledFile, row, 0, 1, 3);
	btnBrowse = new QPushButton(i18n("Browse"));
	btnBrowse->setFlat(true);
	addWidget(btnBrowse, row, 3);
	connect(btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));
	++row;

	cbWidth = new QCheckBox(i18n("Width"));
	addWidget(cbWidth, row, 0);
	sbWidth = new KIntSpinBox(0, 1000, 10, 100, parent);
	sbWidth->setEnabled(false);
	addWidget(sbWidth, row, 1);
	connect(cbWidth, SIGNAL(clicked(bool)), sbWidth, SLOT(setEnabled(bool)));
	cbHeight = new QCheckBox(i18n("Height"));
	addWidget(cbHeight, row, 2);
	sbHeight = new KIntSpinBox(0, 1000, 10, 100, parent);
	sbHeight->setEnabled(false);
	addWidget(sbHeight, row, 3);
	connect(cbHeight, SIGNAL(clicked(bool)), sbHeight, SLOT(setEnabled(bool)));
	++row;

	btnCancel = new QPushButton(i18n("Cancel"));
	addWidget(btnCancel, row, 0);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(exit()));
	btnOk = new QPushButton(i18n("OK"));
	addWidget(btnOk, row, 3);
	connect(btnOk, SIGNAL(clicked()), this, SLOT(addImage()));
}

AddImage::~AddImage()
{
	delete btnCancel;
	delete btnOk;
	delete btnBrowse;
	delete ledFile;
	delete cbHeight;
	delete cbWidth;
	delete sbHeight;
	delete sbWidth;
}

void AddImage::addImage()
{
	if (ledFile->text().isEmpty())
		return;
	QImage image(ledFile->text());
	if (image.isNull())
		return;
	//TODO: show that something was going wrong..

	QString html = "<img src=\"";
	html += ledFile->text() + "\"";
	if (cbWidth->isChecked())
		html += " width=\"" + QString().setNum(sbWidth->value()) + "\"";
	if (cbHeight->isChecked())
		html += " height=\"" + QString().setNum(sbHeight->value()) + "\"";
	html += " >";
	emit addedImage(html);
}

void AddImage::browse()
{
	QString fileName = KFileDialog::getOpenFileName(KUrl(), "*.png *.jpg *.bmp| Image Files\n*|" + i18n("All Files"), parent, i18n("Select Image"));
	ledFile->setText(fileName);
}

void AddImage::exit()
{
	delete this;
}



