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

#include "gui/textfind.h"
#include <QKeySequence>
#include <QHBoxLayout>

TextFind::TextFind(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);

	hideBtn = new QPushButton(QIcon("icons/window-close.png"), "");
	hideBtn->setMaximumWidth(30);
	hideBtn->setFlat(true);
	connect(hideBtn, SIGNAL(clicked()), this, SLOT(hide()));

	layout->addWidget(hideBtn, 0, 0);

	findEdit = new QLineEdit;
	findEdit->setMinimumWidth(150);
	layout->addWidget(findEdit, 0, 1);
	connect(findEdit, SIGNAL(textChanged(const QString &)), this, SLOT(findTextChange(const QString&)));

	prevBtn = new QPushButton(QIcon("icons/go-previous.png"), tr("Previous"));
	prevBtn->setFlat(true);
	layout->addWidget(prevBtn, 0, 2);

	nextBtn = new QPushButton(QIcon("icons/go-next.png"), tr("Next"));
	nextBtn->setFlat(true);
	layout->addWidget(nextBtn, 0, 3);

	QFrame *optionPanel = new QFrame;
	optionPanel->hide();
	QHBoxLayout *optionPanelLayout = new QHBoxLayout;
	optionPanelLayout->setAlignment(Qt::AlignRight);
	caseCbx = new QCheckBox("Match case");
	optionPanelLayout->addWidget(caseCbx);
	wordCbx = new QCheckBox("Match whole word");
	optionPanelLayout->addWidget(wordCbx);
	optionPanel->setLayout(optionPanelLayout);
	layout->addWidget(optionPanel, 2, 0, 4, 0);

	replaceEdit = new QLineEdit;
	replaceEdit->setMinimumWidth(150);
	replaceEdit->hide();
	layout->addWidget(replaceEdit, 1, 1);

	replaceBtn = new QPushButton(tr("Replace"));
	replaceBtn->hide();
	replaceBtn->setFlat(true);
	layout->addWidget(replaceBtn, 1, 2);

	replaceAllBtn = new QPushButton(tr("Replace All"));
	replaceAllBtn->hide();
	replaceAllBtn->setFlat(true);
	layout->addWidget(replaceAllBtn, 1, 3);

	moreBtn = new QPushButton(QIcon("icons/arrow-up-double.png"), tr(""));
	moreBtn->setFlat(true);
	moreBtn->setMaximumWidth(30);
	layout->addWidget(moreBtn, 0, 4);
	lessBtn = new QPushButton(QIcon("icons/arrow-down-double.png"), tr(""));
	lessBtn->setFlat(true);
	lessBtn->setMaximumWidth(30);
	lessBtn->hide();
	layout->addWidget(lessBtn, 0, 4);

	connect(moreBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), moreBtn, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), moreBtn , SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), lessBtn, SLOT(hide()));

	connect(moreBtn, SIGNAL(clicked(bool)), replaceEdit, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), replaceBtn, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), replaceAllBtn, SLOT(show()));
	connect(moreBtn, SIGNAL(clicked(bool)), optionPanel, SLOT(show()));
	connect(lessBtn, SIGNAL(clicked(bool)), replaceEdit, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), replaceBtn, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), replaceAllBtn, SLOT(hide()));
	connect(lessBtn, SIGNAL(clicked(bool)), optionPanel, SLOT(hide()));

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


