/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub, Yves Adler
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

#include "gui/widget/textfind.h"
#include <QKeySequence>
#include <QHBoxLayout>

TextFind::TextFind(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);

	hideBtn = new QPushButton(QIcon(":/icons/actions/window-close.png"), "");
	hideBtn->setMaximumWidth(30);
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn, 0, 0);

	findEdit = new QLineEdit;
	findEdit->setMinimumWidth(150);
	layout->addWidget(findEdit, 0, 1);
	connect(findEdit, SIGNAL(textChanged(const QString &)), this, SLOT(findTextChange(const QString&)));

	prevBtn = new QPushButton(QIcon(":/icons/actions/go-previous.png"), tr("Previous"));
	prevBtn->setFlat(true);
	connect(prevBtn, SIGNAL(clicked()), this, SLOT(prevBtnClicked()));
	layout->addWidget(prevBtn, 0, 2);

	nextBtn = new QPushButton(QIcon(":/icons/actions/go-next.png"), tr("Next"));
	nextBtn->setFlat(true);
	connect(nextBtn, SIGNAL(clicked()), this, SLOT(nextBtnClicked()));
	layout->addWidget(nextBtn, 0, 3);

	moreBtn = new QPushButton(QIcon(":/icons/actions/arrow-up-double.png"), "");
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 4);

	
	replaceEdit = new QLineEdit;
	replaceEdit->setMinimumWidth(150);
	layout->addWidget(replaceEdit, 1, 1);

	replaceBtn = new QPushButton(tr("Replace"));
	replaceBtn->setFlat(true);
	connect(replaceBtn, SIGNAL(clicked()), this, SLOT(replaceBtnClicked()));
	layout->addWidget(replaceBtn, 1, 2);

	replaceAllBtn = new QPushButton(tr("Replace All"));
	replaceAllBtn->setFlat(true);
	connect(replaceAllBtn, SIGNAL(clicked()), this, SLOT(replaceAllBtnClicked()));
	layout->addWidget(replaceAllBtn, 1, 3);


	optionPanel = new QFrame;
	optionLayout = new QHBoxLayout;
	optionLayout->setAlignment(Qt::AlignRight);
	caseCbx = new QCheckBox(tr("Match case"));
	optionLayout->addWidget(caseCbx);
	wordCbx = new QCheckBox(tr("Match whole word"));
	optionLayout->addWidget(wordCbx);
	optionPanel->setLayout(optionLayout);
	layout->addWidget(optionPanel, 2, 0, 4, 0);

	showAll = true;
	showMore();
	connect(moreBtn, SIGNAL(clicked()), this, SLOT(showMore())); 

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
	delete replaceEdit;
	delete nextBtn;
	delete prevBtn;
	delete hideBtn;
	delete moreBtn;
	delete replaceBtn;
	delete replaceAllBtn;
	delete caseCbx;
	delete wordCbx;
	delete optionLayout;
	delete optionPanel;
	delete layout;
	delete abortAction;
}

void TextFind::show()
{
	findEdit->setFocus(Qt::ShortcutFocusReason);
	findTextChange("");
	QWidget::show();
}

void TextFind::nextBtnClicked()
{
	emit findNext();
}

void TextFind::prevBtnClicked()
{
	emit findPrev();
}

void TextFind::replaceBtnClicked()
{
	emit replace();
}

void TextFind::replaceAllBtnClicked()
{
	emit replaceAll();
}

void TextFind::showMore()
{
	optionPanel->setHidden(showAll);
	replaceEdit->setHidden(showAll);
	replaceBtn->setHidden(showAll);
	replaceAllBtn->setHidden(showAll);
	if (showAll)
	{
		moreBtn->setIcon(QIcon(":/icons/actions/arrow-up-double.png"));
		showAll = false;
	} else {
		moreBtn->setIcon(QIcon(":/icons/actions/arrow-down-double.png"));
		showAll = true;
	}
}

QString TextFind::getSearchString()
{
	return findEdit->text();
}

QString TextFind::getReplaceString()
{
	return replaceEdit->text();
}

bool TextFind::getCaseSensitivity()
{
	return caseCbx->isChecked();
}

bool TextFind::getWholeWord()
{
	return wordCbx->isChecked();
}

void TextFind::findTextChange(const QString &text)
{
	if (text.isEmpty())
	{
		nextBtn->setEnabled(false);
		prevBtn->setEnabled(false);
		replaceBtn->setEnabled(false);
		replaceAllBtn->setEnabled(false);
	} else {
		nextBtn->setEnabled(true);
		prevBtn->setEnabled(true);
		replaceBtn->setEnabled(true);
		replaceAllBtn->setEnabled(true);
	}
	emit searchStringChanged(text);
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



