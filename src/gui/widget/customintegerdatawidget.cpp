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

#include "src/gui/widget/customintegerdatawidget.h"


CustomIntegerDataWidget::CustomIntegerDataWidget(CustomNodeItem *item)
{
	layout = new QVBoxLayout;
	spinbox = new QSpinBox;
	layout->addWidget(spinbox);
	setLayout(layout);

	this->item = item;
	spinbox->setValue(item->getData().toInt());

	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(onChange()));
}

CustomIntegerDataWidget::~CustomIntegerDataWidget()
{
	delete layout;
	delete spinbox;
}

void CustomIntegerDataWidget::save()
{
	item->setData(getData());
}

void CustomIntegerDataWidget::setData(QString data)
{
	spinbox->setValue(data.toInt());
	onChange();
}

QString CustomIntegerDataWidget::getData() const
{
	return QString::number(spinbox->value());
}

void CustomIntegerDataWidget::onChange()
{
	emit changed();
}


