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

#include <kfiledialog.h>
#include <klocalizedstring.h>
#include "src/gui/widget/customimagedatawidget.h"


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

void CustomImageDataWidget::save()
{
	item->setData(fileName);
}

void CustomImageDataWidget::mousePressEvent(QMouseEvent*)
{
	QString tmpFileName = KFileDialog::getOpenFileName(KUrl(), "*.png *.jpg *.bmp| " + i18n("Image Files") + "\n*| "+ i18n("All Files"), this, i18n("Select Image"));

	if (tmpFileName.isEmpty())
		return;
	QImage image(tmpFileName);
	if (!image.isNull())
	{
		setPixmap(QPixmap::fromImage(image));
		fileName = tmpFileName;
	}
}


