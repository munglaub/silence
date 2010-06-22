/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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
#include "src/gui/widget/syntaxbox.h"


SyntaxBox::SyntaxBox(bool showLabel, QWidget *parent)
	: QWidget(parent)
{
	layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	
	lblSyntax = new QLabel(i18n("Syntax:"));
	lblSyntax->setVisible(showLabel);
	layout->addWidget(lblSyntax);

	synbox = new KComboBox;
	synbox->addItem(i18nc("no syntax selected", "None"));

	synbox->addItem("Bash");
	synbox->addItem("Batch");
	synbox->addItem("CMake");
	synbox->addItem("C++");
	synbox->addItem("C#");
	synbox->addItem("CSS");
	synbox->addItem("D");
	synbox->addItem("Diff");
	synbox->addItem("HTML");
	synbox->addItem("IDL");
	synbox->addItem("Java");
	synbox->addItem("JavaScript");
	synbox->addItem("Lua");
	synbox->addItem("Makefile");
	synbox->addItem("Perl");
	synbox->addItem("POV");
	synbox->addItem("Python");
	synbox->addItem("Ruby");
	synbox->addItem("SQL");
	synbox->addItem("LaTeX");
	synbox->addItem("VHDL");

	layout->addWidget(synbox);
	setLayout(layout);
}

SyntaxBox::~SyntaxBox()
{
	delete synbox;
	delete lblSyntax;
	delete layout;
}

QString SyntaxBox::getSyntax()
{
	return synbox->currentText();
}

void SyntaxBox::setSyntax(QString syntax)
{
	synbox->setCurrentIndex(synbox->findText(syntax));
}



