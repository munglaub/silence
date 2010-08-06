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

#include "src/gui/view/customcontentview.h"
#include <klocalizedstring.h>


CustomContentView::CustomContentView()
{
	layout = new QVBoxLayout;
	scrollarea = new QScrollArea;
	layout->addWidget(scrollarea);
	scrolllayout = new QVBoxLayout;
	scrolllayout->setAlignment(Qt::AlignTop);

	btnSave = new QPushButton(i18n("Save"));
	scrolllayout->addWidget(btnSave, 0, Qt::AlignRight);
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));

	scrollarea->setLayout(scrolllayout);
	setLayout(layout);
}

CustomContentView::~CustomContentView()
{
	// TODO: implement
}

void CustomContentView::setItems(QList<CustomNodeItem*> items)
{
	while (!elements.isEmpty())
	{
		scrolllayout->removeWidget(elements.first());
		delete elements.takeFirst();
	}
	for (int i = 0; i < items.size(); ++i)
	{
		CustomNodeElement *element = new CustomNodeElement(items.at(i));
		scrolllayout->insertWidget(i, element);
		elements.append(element);
	}
}
	
bool CustomContentView::hasChanged()
{
	// TODO: implement
	return false;
}

AbstractContentChange* CustomContentView::getChange()
{
	// TODO: implement
	return 0;
}

void CustomContentView::save()
{
	for (int i = 0; i < elements.size(); ++i)
		elements.at(i)->save();
}



