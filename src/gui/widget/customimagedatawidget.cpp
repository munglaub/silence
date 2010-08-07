/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#include "src/gui/widget/customimagedatawidget.h"
#include <kfiledialog.h>
#include <klocalizedstring.h>

CustomImageDataWidget::CustomImageDataWidget(CustomNodeItem *item)
{
	// TODO: provide a method to empty the picture..
	this->item = item;
	fileName = item->getData();
	setToolTip(i18n("Click to change the image"));
	if (item->getData().isEmpty())
	{
		setText(i18n("Click to add an image"));
	} else {
		QImage image(item->getData());
		if (!image.isNull())
			setPixmap(QPixmap::fromImage(image));
		else
			setText(i18n("Click to add an image"));
	}
}

CustomImageDataWidget::~CustomImageDataWidget()
{
	// TODO: implement
}

void CustomImageDataWidget::save()
{
	item->setData(fileName);
}

void CustomImageDataWidget::mousePressEvent(QMouseEvent *event)
{
	QString tmpFileName = KFileDialog::getOpenFileName(KUrl(), "*.png *.jpg *.bmp| Image Files\n*|All Files", this, "Select Image");

	if (tmpFileName.isEmpty())
		return;
	QImage image(tmpFileName);
	if (!image.isNull())
	{
		setPixmap(QPixmap::fromImage(image));
		fileName = tmpFileName;
	}
}

