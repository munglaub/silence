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

#include "src/gui/widget/customtextdatawidget.h"


CustomTextDataWidget::CustomTextDataWidget(CustomNodeItem *item)
{
	layout = new QVBoxLayout;
	textedit = new QTextEdit;
	layout->addWidget(textedit);
	setLayout(layout);

	this->item = item;
	textedit->setHtml(item->getData());

	connect(textedit, SIGNAL(textChanged()), this, SLOT(onChange()));
}

CustomTextDataWidget::~CustomTextDataWidget()
{
	delete layout;
	delete textedit;
}

void CustomTextDataWidget::save()
{
	item->setData(textedit->toHtml());
}

void CustomTextDataWidget::setData(QString data)
{
	textedit->setHtml(data);
	onChange();
}

QString CustomTextDataWidget::getData() const
{
	return textedit->toHtml();
}

void CustomTextDataWidget::onChange()
{
	emit changed();
}


