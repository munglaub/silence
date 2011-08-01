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

#include <KIcon>
#include <klocalizedstring.h>
#include "src/gui/widget/custombooleandatawidget.h"
#include "src/gui/widget/customimagedatawidget.h"
#include "src/gui/widget/customintegerdatawidget.h"
#include "src/gui/widget/customnodeelement.h"
#include "src/gui/widget/customnumberdatawidget.h"
#include "src/gui/widget/customstringdatawidget.h"
#include "src/gui/widget/customtextdatawidget.h"


CustomNodeElement::CustomNodeElement(CustomNodeItem *item, bool showModifiers, QWidget *parent)
	: QWidget(parent)
{
	this->item = item;
	layout = new QHBoxLayout;

	caption = new QLabel(item->getCaption());
	layout->addWidget(caption);

	datawidget = 0;

	switch (item->getType()){
		case CustomNodeItem::String:
				datawidget = new CustomStringDataWidget(item);
			break;
		case CustomNodeItem::Text:
				datawidget = new CustomTextDataWidget(item);
			break;
		case CustomNodeItem::Integer:
				datawidget = new CustomIntegerDataWidget(item);
			break;
		case CustomNodeItem::Number:
				datawidget = new CustomNumberDataWidget(item);
			break;
		case CustomNodeItem::Boolean:
				datawidget = new CustomBooleanDataWidget(item);
			break;
		case CustomNodeItem::Image:
				datawidget = new CustomImageDataWidget(item);
			break;
	}
	if (datawidget)
	{
		layout->addWidget(datawidget);
		connect(datawidget, SIGNAL(changed()), this, SLOT(onChange()));
	}

	btnRemove = new QPushButton(KIcon("edit-delete"), "");
	btnRemove->setFlat(true);
	btnRemove->setMaximumWidth(30);
	btnRemove->setToolTip(i18n("Remove Item"));
	btnRemove->setVisible(showModifiers);
	layout->addWidget(btnRemove);
	connect(btnRemove, SIGNAL(clicked()), this, SLOT(onRemove()));
	setLayout(layout);
}

CustomNodeElement::~CustomNodeElement()
{
	delete datawidget;
	delete btnRemove;
	delete caption;
	delete layout;
}

void CustomNodeElement::setData(QString data)
{
	if (datawidget)
		datawidget->setData(data);
}

QString CustomNodeElement::getData() const
{
	if (datawidget)
		return datawidget->getData();
	else
		return "";
}

void CustomNodeElement::onRemove()
{
	emit remove(this, item);
}

void CustomNodeElement::onChange()
{
	emit changed();
}

void CustomNodeElement::save()
{
	if (datawidget)
		datawidget->save();
}



