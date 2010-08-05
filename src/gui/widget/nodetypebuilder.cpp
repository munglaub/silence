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

#include "src/gui/widget/nodetypebuilder.h"
#include <klocalizedstring.h>


NodeTypeBuilder::NodeTypeBuilder()
{
	def = 0;
	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);

//TODO: so eine VORSICHT! warnung hinmalen wo steht das es unwahrscheinlich unguenstige auswirkungen auf vorhandene daten haben kann wenn man da einen nodetype veraendert..

// ein panel mit den neues element erstellen dingern
	buildpane = new QGroupBox;
	layout->addWidget(buildpane);
	buildlayout = new QGridLayout;
	buildlayout->setAlignment(Qt::AlignTop);
	lblElementCaption = new QLabel(i18n("Caption"));
	buildlayout->addWidget(lblElementCaption, 0, 0);
	leElementCaption = new QLineEdit;
	buildlayout->addWidget(leElementCaption, 1, 0, 1, 1, Qt::AlignTop);
	connect(leElementCaption, SIGNAL(textChanged(const QString &)), this, SLOT(updateBtnAddElement()));

	lblElementTypes = new QLabel(i18n("Element Type"));
	buildlayout->addWidget(lblElementTypes, 0, 1);
	elementTypes = new QListWidget;
	buildlayout->addWidget(elementTypes, 1, 1, 1, 1, Qt::AlignTop);
	elementTypes->addItem(new QListWidgetItem("String", elementTypes, CustomNodeItem::String));
	elementTypes->addItem(new QListWidgetItem("Text", elementTypes, CustomNodeItem::Text));
	elementTypes->addItem(new QListWidgetItem("Integer", elementTypes, CustomNodeItem::Integer));
	elementTypes->addItem(new QListWidgetItem("Number", elementTypes, CustomNodeItem::Number));
	elementTypes->addItem(new QListWidgetItem("Boolean", elementTypes, CustomNodeItem::Boolean));
	elementTypes->addItem(new QListWidgetItem("Image", elementTypes, CustomNodeItem::Image));

	btnAddElement = new QPushButton(i18n("Add Element"));
	buildlayout->addWidget(btnAddElement, 1, 2, 1, 1, Qt::AlignBottom);
	connect(btnAddElement, SIGNAL(clicked()), this, SLOT(addElement()));

	buildpane->setLayout(buildlayout);

// ein panel mit einer vorschau wie das aussieht und knoepfen zum element entfernen
	prevpane = new QGroupBox(i18n("Preview")); //TODO: bessere ueberschrift ausdenken
	//TODO: scrollbar machen
	prevlayout = new QVBoxLayout;
	prevpane->setLayout(prevlayout);
	layout->addWidget(prevpane);


	layout->addStretch();


	// Buttons
	//TODO: btnAbort entfernen
	QHBoxLayout *btnLayout = new QHBoxLayout;
	QPushButton *btnAbort = new QPushButton(i18n("Abort"));
	btnLayout->addWidget(btnAbort);
	connect(btnAbort, SIGNAL(clicked()), this, SLOT(onClose()));

	QPushButton *btnSave = new QPushButton(i18n("Save Node Type"));
	//layout->addWidget(btnSave, 0, Qt::AlignRight);
	btnLayout->addWidget(btnSave);
	connect(btnSave, SIGNAL(clicked()), this, SLOT(onClose()));

	layout->addLayout(btnLayout);


	setLayout(layout);
	updateBtnAddElement();
}

NodeTypeBuilder::~NodeTypeBuilder()
{
	// TODO: implement
}

void NodeTypeBuilder::show(CustomNodeTypeDefinition *def)
{
	clearPrevlayout();
	this->def = def;
	buildpane->setTitle(def->getName()); // Vieleicht noch was davor schreiben oder so..
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
	CustomNodeItem::Type type = (CustomNodeItem::Type)elementTypes->currentItem()->type();
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
	CustomNodeElement *itemwidget = new CustomNodeElement(item);
	prevlayout->addWidget(itemwidget);
	elements.append(itemwidget);

	connect(itemwidget, SIGNAL(remove(CustomNodeElement*, CustomNodeItem*)), this, SLOT(removeItem(CustomNodeElement*, CustomNodeItem*)));
}


