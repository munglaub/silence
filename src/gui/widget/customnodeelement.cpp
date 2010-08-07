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
			{
				CustomStringDataWidget *tmp = new CustomStringDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
		case CustomNodeItem::Text:
			{
				CustomTextDataWidget *tmp = new CustomTextDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
		case CustomNodeItem::Integer:
			{
				CustomIntegerDataWidget *tmp = new CustomIntegerDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
		case CustomNodeItem::Number:
			{
				CustomNumberDataWidget *tmp = new CustomNumberDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
		case CustomNodeItem::Boolean:
			{
				CustomBooleanDataWidget *tmp = new CustomBooleanDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
		case CustomNodeItem::Image:
			{
				CustomImageDataWidget *tmp = new CustomImageDataWidget(item);
				layout->addWidget(tmp);
				datawidget = tmp;
			}
			break;
	}


	btnRemove = new QPushButton(i18n("Remove"));
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

void CustomNodeElement::onRemove()
{
	emit remove(this, item);
}

void CustomNodeElement::save()
{
	if (datawidget)
		datawidget->save();
}



