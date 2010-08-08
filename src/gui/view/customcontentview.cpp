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
#include "src/controller.h"
#include "src/data/node/customcontentchange.h"
#include "src/gui/view/customcontentview.h"


CustomContentView::CustomContentView()
{
	isChanged = false;

	layout = new QVBoxLayout;
	scrollarea = new QScrollArea;
	layout->addWidget(scrollarea);
	scrolllayout = new QVBoxLayout;
	scrolllayout->setAlignment(Qt::AlignTop);

	btnSave = new QPushButton(i18n("Save"));
	btnSave->setShortcut(QKeySequence::Save);
	scrolllayout->addWidget(btnSave, 0, Qt::AlignRight);
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));

	scrollarea->setLayout(scrolllayout);
	setLayout(layout);
}

CustomContentView::~CustomContentView()
{
	deleteElements();
	delete btnSave;
	delete scrolllayout;
	delete scrollarea;
	delete layout;
}

void CustomContentView::setItems(QList<CustomNodeItem*> items)
{
	deleteElements();
	this->items = items;
	for (int i = 0; i < items.size(); ++i)
	{
		CustomNodeElement *element = new CustomNodeElement(items.at(i));
		connect(element, SIGNAL(changed()), this, SLOT(contentChanged()));
		scrolllayout->insertWidget(i, element);
		elements.append(element);
	}
	isChanged = false;
	Controller::create()->getStatusBar()->setSaveStatus(true);
}
	
bool CustomContentView::hasChanged()
{
	return isChanged;
}

AbstractContentChange* CustomContentView::getChange()
{
	QStringList data;
	for (int i = 0; i < elements.size(); ++i)
		data.append(elements.at(i)->getData());
	return new CustomContentChange(items, data, this);
}

void CustomContentView::setData(QStringList data)
{
	if (data.size() == elements.size())
		for (int i = 0; i < data.size(); ++i)
			elements.at(i)->setData(data.at(i));
}

void CustomContentView::save()
{
	for (int i = 0; i < elements.size(); ++i)
		elements.at(i)->save();
	isChanged = false;
	Controller::create()->getStatusBar()->setSaveStatus(true);
}

void CustomContentView::contentChanged()
{
	Controller::create()->getStatusBar()->setSaveStatus(false);
	isChanged = true;
}

void CustomContentView::deleteElements()
{
	while (!elements.isEmpty())
	{
		scrolllayout->removeWidget(elements.first());
		delete elements.takeFirst();
	}
}


