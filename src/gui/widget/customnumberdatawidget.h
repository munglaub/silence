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

#ifndef CUSTOMNUMBERDATAWIDGET_H
#define CUSTOMNUMBERDATAWIDGET_H

#include <QDoubleSpinBox>
#include "src/gui/widget/customdatawidget.h"
#include "src/data/node/customnodeitem.h"


class CustomNumberDataWidget : public CustomDataWidget, public QDoubleSpinBox
{
	public:
		CustomNumberDataWidget(CustomNodeItem *item);
		~CustomNumberDataWidget();

		void save();

	private:
		CustomNodeItem *item;
};

#endif // CUSTOMNUMBERDATAWIDGET_H

