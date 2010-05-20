/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
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
#include "src/gui/widget/inputwidget.h"


InputWidget::InputWidget(QWidget *parent)
	: QGroupBox(parent)
{
	layout = new QGridLayout;
	inputEdit = new KLineEdit;
	inputEdit->setClearButtonShown(true);
	layout->addWidget(inputEdit, 0, 0, 1, 2);
	cancelBtn = new QPushButton(i18n("Cancel"));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(hide()));
	layout->addWidget(cancelBtn, 1, 0);
	okBtn = new QPushButton(i18n("OK"));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(confirm()));
	layout->addWidget(okBtn, 1, 1);
	setLayout(layout);
	
	connect(inputEdit, SIGNAL(returnPressed()), this, SLOT(confirm()));
}

InputWidget::~InputWidget()
{
	delete cancelBtn;
	delete okBtn;
	delete inputEdit;
	delete layout;
}

void InputWidget::show(QString title)
{
	setTitle(title);
	inputEdit->clear();
	QGroupBox::show();
	inputEdit->setFocus();
}

QString InputWidget::getInput()
{
	return inputEdit->text();
}

void InputWidget::confirm()
{
	emit done();
}




