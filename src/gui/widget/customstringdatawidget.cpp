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

#include "src/gui/widget/customstringdatawidget.h"


CustomStringDataWidget::CustomStringDataWidget(CustomNodeItem *item)
{
	layout = new QVBoxLayout;
	edit = new QLineEdit;
	layout->addWidget(edit);
	setLayout(layout);

	this->item = item;
	edit->setText(item->getData());

	connect(edit, SIGNAL(textChanged(const QString&)), this, SLOT(onChange()));
}

CustomStringDataWidget::~CustomStringDataWidget()
{
	delete edit;
	delete layout;
}

void CustomStringDataWidget::save()
{
	item->setData(edit->text());
}

void CustomStringDataWidget::setData(QString data)
{
	edit->setText(data);
	onChange();
}

QString CustomStringDataWidget::getData() const
{
	return edit->text();
}

void CustomStringDataWidget::onChange()
{
	emit changed();
}


