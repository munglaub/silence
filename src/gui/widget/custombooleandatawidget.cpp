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

#include "src/gui/widget/custombooleandatawidget.h"


CustomBooleanDataWidget::CustomBooleanDataWidget(CustomNodeItem *item)
{
	layout = new QVBoxLayout;
	checkbox = new QCheckBox;
	layout->addWidget(checkbox);
	setLayout(layout);
	this->item = item;
	checkbox->setChecked(item->getData() == "True");
	connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(onChange()));
}

CustomBooleanDataWidget::~CustomBooleanDataWidget()
{
	delete checkbox;
	delete layout;
}

void CustomBooleanDataWidget::save()
{
	item->setData(getData());
}

void CustomBooleanDataWidget::setData(QString data)
{
	checkbox->setChecked(data == "True");
	onChange();
}

QString CustomBooleanDataWidget::getData() const
{
	if (checkbox->isChecked())
		return "True";
	else
		return "False";
}

void CustomBooleanDataWidget::onChange()
{
	emit changed();
}


