/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
 * Copyright (C) 2009, 2010 Yves Adler <yves.adler@googlemail.com>
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

#include <KIcon>
#include <klocalizedstring.h>
#include <QHBoxLayout>
#include <QKeySequence>
#include "src/gui/widget/textfind.h"


TextFind::TextFind(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);

	hideBtn = new QPushButton(KIcon("window-close"), "");
	hideBtn->setMaximumWidth(30);
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn, 0, 0);

	findEdit = new KLineEdit;
	findEdit->setClearButtonShown(true);
	findEdit->setMinimumWidth(150);
	layout->addWidget(findEdit, 0, 1);
	connect(findEdit, SIGNAL(textChanged(const QString &)), this, SLOT(findTextChange(const QString&)));

	prevBtn = new QPushButton(KIcon("go-previous"), i18n("Previous"));
	prevBtn->setFlat(true);
	connect(prevBtn, SIGNAL(clicked()), this, SLOT(prevBtnClicked()));
	layout->addWidget(prevBtn, 0, 2);

	nextBtn = new QPushButton(KIcon("go-next"), i18n("Next"));
	nextBtn->setFlat(true);
	connect(nextBtn, SIGNAL(clicked()), this, SLOT(nextBtnClicked()));
	layout->addWidget(nextBtn, 0, 3);

	moreBtn = new QPushButton(KIcon("arrow-up-double"), "");
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 4);

	
	replaceEdit = new KLineEdit;
	replaceEdit->setClearButtonShown(true);
	replaceEdit->setMinimumWidth(150);
	layout->addWidget(replaceEdit, 1, 1);

	replaceBtn = new QPushButton(i18n("Replace"));
	replaceBtn->setFlat(true);
	connect(replaceBtn, SIGNAL(clicked()), this, SLOT(replaceBtnClicked()));
	layout->addWidget(replaceBtn, 1, 2);

	replaceAllBtn = new QPushButton(i18n("Replace All"));
	replaceAllBtn->setFlat(true);
	connect(replaceAllBtn, SIGNAL(clicked()), this, SLOT(replaceAllBtnClicked()));
	layout->addWidget(replaceAllBtn, 1, 3);


	optionPanel = new QFrame;
	optionLayout = new QHBoxLayout;
	optionLayout->setAlignment(Qt::AlignRight);
	caseCbx = new QCheckBox(i18n("Match case"));
	optionLayout->addWidget(caseCbx);
	wordCbx = new QCheckBox(i18n("Match whole word"));
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
		moreBtn->setIcon(KIcon("arrow-up-double"));
		showAll = false;
	} else {
		moreBtn->setIcon(KIcon("arrow-down-double"));
		showAll = true;
	}
}

void TextFind::showFull()
{
	show();
	if (!showAll)
		showMore();
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



