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
	layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignTop);

// ein panel mit den neues element erstellen dingern
	buildpane = new QGroupBox;
	layout->addWidget(buildpane);
	buildlayout = new QGridLayout;
	buildlayout->setAlignment(Qt::AlignTop);
	lblElementCaption = new QLabel(i18n("Caption"));
	buildlayout->addWidget(lblElementCaption, 0, 0);
	leElementCaption = new QLineEdit;
	buildlayout->addWidget(leElementCaption, 1, 0, 1, 1, Qt::AlignTop);

	lblElementTypes = new QLabel(i18n("Element Type"));
	buildlayout->addWidget(lblElementTypes, 0, 1);
	elementTypes = new QListWidget;
	buildlayout->addWidget(elementTypes, 1, 1, 1, 1, Qt::AlignTop);
	elementTypes->addItem("Line of Text");
	elementTypes->addItem("Text");
	elementTypes->addItem("Integer");
	elementTypes->addItem("Checkbox");
	elementTypes->addItem("Picture");

	btnAddElement = new QPushButton(i18n("Add Element"));
	buildlayout->addWidget(btnAddElement, 1, 2, 1, 1, Qt::AlignBottom);

	buildpane->setLayout(buildlayout);

// ein panel mit einer vorschau wie das aussieht und knoepfen zum element entfernen
	QGroupBox *blubb = new QGroupBox("foobar");
	QVBoxLayout *blubblayout = new QVBoxLayout;
	blubb->setLayout(blubblayout);
	layout->addWidget(blubb);

	layout->addStretch();


	//TODO: unterscheidung zwischen ok und abbrechen
	// -> oder kein abbrechen?
	QPushButton *btnClose = new QPushButton(i18n("Close"));
	layout->addWidget(btnClose);
	connect(btnClose, SIGNAL(clicked()), this, SLOT(onClose()));

	setLayout(layout);
}

NodeTypeBuilder::~NodeTypeBuilder()
{
	// TODO: implement
}

void NodeTypeBuilder::show(QString name)
{
	buildpane->setTitle(name); // Vieleicht noch was davor schreiben oder so..
	setVisible(true);
	//TODO:
	// - gucken ob es den typ schon gibt
	//	-> wenn ja laden
}

void NodeTypeBuilder::onClose()
{
	emit close();
}



