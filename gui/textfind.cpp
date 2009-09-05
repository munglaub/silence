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

#include "gui/textfind.h"
#include <QKeySequence>

TextFind::TextFind(QWidget *parent)
	: QWidget(parent)
{
	layout = new QHBoxLayout;
	layout->setAlignment(Qt::AlignLeft);
	layout->setContentsMargins(0, 0, 0, 0);

	hideBtn = new QPushButton(QIcon("icons/window-close.png"), "");
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn);

	findEdit = new QLineEdit;
	findEdit->setMinimumWidth(150);
	layout->addWidget(findEdit);
	connect(findEdit, SIGNAL(textChanged(const QString &)), this, SLOT(findTextChange(const QString&)));

	prevBtn = new QPushButton(QIcon("icons/go-previous.png"), tr("Previous"));
	prevBtn->setFlat(true);
	layout->addWidget(prevBtn);

	nextBtn = new QPushButton(QIcon("icons/go-next.png"), tr("Next"));
	nextBtn->setFlat(true);
	layout->addWidget(nextBtn);
	
	caseCbx = new QCheckBox("Match case");
	layout->addWidget(caseCbx);
	wordCbx = new QCheckBox("Match whole word");
	layout->addWidget(wordCbx);

	setLayout(layout);
	connect(findEdit, SIGNAL(returnPressed()), nextBtn, SLOT(click()));

	abortAction = new QAction(this);
	abortAction->setShortcut(QKeySequence("Escape"));
	this->addAction(abortAction);
	connect(abortAction, SIGNAL(triggered(bool)), this, SLOT(hide()));
}

TextFind::~TextFind()
{
	delete findEdit;
	delete nextBtn;
	delete prevBtn;
	delete hideBtn;
	delete caseCbx;
	delete wordCbx;
	delete layout;
	delete abortAction;
}

void TextFind::show()
{
	findEdit->setFocus(Qt::ShortcutFocusReason);
	findTextChange("");
	QWidget::show();
}

QString TextFind::getSearchString()
{
	return findEdit->text();
}

bool TextFind::getCaseSensitivity()
{
	return caseCbx->isChecked();
}

bool TextFind::getWholeWord()
{
	return wordCbx->isChecked();
}

QPushButton* TextFind::getPrevBtn()
{
	return prevBtn;
}

QPushButton* TextFind::getNextBtn()
{
	return nextBtn;
}

void TextFind::findTextChange(const QString &text)
{
	if (text.isEmpty())
	{
		nextBtn->setEnabled(false);
		prevBtn->setEnabled(false);
	} else {
		nextBtn->setEnabled(true);
		prevBtn->setEnabled(true);
	}
}

void TextFind::setFound(bool found)
{
	QPalette palette = findEdit->palette();
	if (found)
		palette.setColor(QPalette::Active, QPalette::Base, QColor(255, 255, 255));
	else
		palette.setColor(QPalette::Active, QPalette::Base, QColor(255, 102, 102));
	findEdit->setPalette(palette);
}

QLineEdit* TextFind::getFindEdit()
{
	return findEdit;
}


