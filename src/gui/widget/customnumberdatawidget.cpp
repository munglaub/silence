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

#include <limits>
#include "src/gui/widget/customnumberdatawidget.h"


CustomNumberDataWidget::CustomNumberDataWidget(CustomNodeItem *item)
{
	layout = new QVBoxLayout;
	spinbox = new QDoubleSpinBox;
	layout->addWidget(spinbox);
	setLayout(layout);

	this->item = item;
	spinbox->setMaximum(std::numeric_limits<double>::max());
	spinbox->setMinimum(-std::numeric_limits<double>::max());
	spinbox->setDecimals(4);
	spinbox->setValue(item->getData().toDouble());

	connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(onChange()));
}

CustomNumberDataWidget::~CustomNumberDataWidget()
{
	delete spinbox;
	delete layout;
}

void CustomNumberDataWidget::save()
{
	item->setData(getData());
}

void CustomNumberDataWidget::setData(QString data)
{
	spinbox->setValue(data.toDouble());
	onChange();
}

QString CustomNumberDataWidget::getData() const
{
	return QString::number(spinbox->value());
}

void CustomNumberDataWidget::onChange()
{
	emit changed();
}


