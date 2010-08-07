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

#ifndef CUSTOMIMAGEDATAWIDGET_H
#define CUSTOMIMAGEDATAWIDGET_H

#include <QLabel>
#include "src/data/node/customnodeitem.h"
#include "src/gui/widget/customdatawidget.h"


/*!\class CustomImageDataWidget
 * \brief A widget for a CustomNodeItem with image data
 *
 * Displays an image.
 *
 * \author Manuel Unglaub
 */
class CustomImageDataWidget : public CustomDataWidget, public QLabel
{
	public:
		/*! The constructor.
		 *
		 * Constructs the CustomImageDataWidget.
		 * \param item The data of this CustomNodeItem will be displayed.
		 */
		CustomImageDataWidget(CustomNodeItem *item);

		void save();

	private:
		CustomNodeItem *item;
		QString fileName;

		void mousePressEvent(QMouseEvent *event);
};

#endif // CUSTOMIMAGEDATAWIDGET_H

