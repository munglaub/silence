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
#include "src/gui/widget/nodetypebuilder.h"


NodeTypeBuilder::NodeTypeBuilder()
{
	def = 0;
	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);

	buildpane = new QGroupBox;
	layout->addWidget(buildpane);

	buildlayout = new QFormLayout;
	buildlayout->setAlignment(Qt::AlignTop);

	leElementCaption = new QLineEdit;
	connect(leElementCaption, SIGNAL(textChanged(const QString &)), this, SLOT(updateBtnAddElement()));
	buildlayout->addRow(i18n("Caption"), leElementCaption);

	elementTypes = new QComboBox;
	elementTypes->addItem(i18n("String"));
	elementTypes->addItem(i18n("Text"));
	elementTypes->addItem(i18n("Integer"));
	elementTypes->addItem(i18n("Number"));
	elementTypes->addItem(i18n("Boolean"));
	elementTypes->addItem(i18n("Image"));
	buildlayout->addRow(i18n("Element Type"), elementTypes);

	btnAddElement = new QPushButton(i18n("Add Element"));
	buildlayout->addRow("", btnAddElement);
	connect(btnAddElement, SIGNAL(clicked()), this, SLOT(addElement()));

	buildpane->setLayout(buildlayout);

	btnClose = new QPushButton(i18n("Close"));
	btnClose->setMinimumWidth(100);
	layout->addWidget(btnClose, 0, Qt::AlignRight);
	connect(btnClose, SIGNAL(clicked()), this, SLOT(onClose()));

	prevpane = new QGroupBox(i18n("Preview"));
	prevlayout = new QVBoxLayout;
	prevpane->setLayout(prevlayout);
	layout->addWidget(prevpane);

	setLayout(layout);
	updateBtnAddElement();
}

NodeTypeBuilder::~NodeTypeBuilder()
{
	clearPrevlayout();
	delete btnClose;
	delete btnAddElement;
	delete elementTypes;
	delete leElementCaption;
	delete buildlayout;
	delete prevlayout;
	delete prevpane;
	delete buildpane;
	delete layout;
}

void NodeTypeBuilder::show(CustomNodeTypeDefinition *def)
{
	clearPrevlayout();
	this->def = def;
	buildpane->setTitle(def->getName());
	setVisible(true);

	// show existing elements
	for (int i = 0; i < def->getItemList().size(); ++i)
		addElementToPrevlayout(def->getItemList().at(i));
}

CustomNodeTypeDefinition* NodeTypeBuilder::getCustomNodeTypeDefinition()
{
	return def;
}

void NodeTypeBuilder::onClose()
{
	emit close();
}

void NodeTypeBuilder::addElement()
{
	CustomNodeItem::Type type = (CustomNodeItem::Type)elementTypes->currentIndex();
	QString caption = leElementCaption->text();
	CustomNodeItem *item = new CustomNodeItem(caption, type);
	def->addItem(item);

	addElementToPrevlayout(item);
	leElementCaption->setText("");
}

void NodeTypeBuilder::updateBtnAddElement()
{
	btnAddElement->setEnabled(!leElementCaption->text().isEmpty());
}

void NodeTypeBuilder::removeItem(CustomNodeElement* element, CustomNodeItem *item)
{
	def->removeItem(item);
	prevlayout->removeWidget(element);
	elements.removeOne(element);
	delete element;
}

void NodeTypeBuilder::clearPrevlayout()
{
	while (!elements.isEmpty())
	{
		CustomNodeElement *tmp = elements.takeFirst();
		prevlayout->removeWidget(tmp);
		delete tmp;
	}
}

void NodeTypeBuilder::addElementToPrevlayout(CustomNodeItem *item)
{
	CustomNodeElement *itemwidget = new CustomNodeElement(item, true);
	prevlayout->addWidget(itemwidget);
	elements.append(itemwidget);

	connect(itemwidget, SIGNAL(remove(CustomNodeElement*, CustomNodeItem*)), this, SLOT(removeItem(CustomNodeElement*, CustomNodeItem*)));
}


