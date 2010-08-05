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

#include "src/gui/widget/customnodeelement.h"
#include <klocalizedstring.h>


CustomNodeElement::CustomNodeElement(CustomNodeItem *item, QWidget *parent)
	: QWidget(parent)
{
	this->item = item;
	layout = new QHBoxLayout;

	layout->addWidget(new QLabel(item->getCaption()));

	switch (item->getType()){
		case CustomNodeItem::String:
			layout->addWidget(new QLineEdit);
			break;
		case CustomNodeItem::Text:
			layout->addWidget(new QTextEdit);
			break;
		case CustomNodeItem::Integer:
			layout->addWidget(new QSpinBox);
			break;
		case CustomNodeItem::Number:
			layout->addWidget(new QLineEdit);
			break;
		case CustomNodeItem::Boolean:
			layout->addWidget(new QCheckBox);
			break;
		case CustomNodeItem::Image:
			layout->addWidget(new QLabel("Image"));
			break;
	}


	btnRemove = new QPushButton(i18n("Remove"));
	layout->addWidget(btnRemove);
	connect(btnRemove, SIGNAL(clicked()), this, SLOT(onRemove()));
	setLayout(layout);
}

void CustomNodeElement::onRemove()
{
	emit remove(this, item);
}

CustomNodeElement::~CustomNodeElement()
{
	// TODO: implement
}


