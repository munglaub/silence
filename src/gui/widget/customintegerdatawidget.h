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

#ifndef CUSTOMINTEGERDATAWIDGET_H
#define CUSTOMINTEGERDATAWIDGET_H

#include <QSpinBox>
#include "src/data/node/customnodeitem.h"
#include "src/gui/widget/customdatawidget.h"


/*!\class CustomIntegerDataWidget
 * \brief A widget for a CustomNodeItem with integer data
 *
 * A spinbox to represent an integer.
 *
 * \author Manuel Unglaub
 */
class CustomIntegerDataWidget : public CustomDataWidget, public QSpinBox
{
	public:
		/*! The constructor.
		 *
		 * Constructs the CustomIntegerDataWidget.
		 * \param item The data of this CustomNodeItem will be displayed.
		 */
		CustomIntegerDataWidget(CustomNodeItem *item);

		void save();

	private:
		CustomNodeItem *item;
};

#endif // CUSTOMINTEGERDATAWIDGET_H

