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

#include <KIcon>
#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/gui/widget/labellist.h"


LabelList::LabelList(QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	showOptions = false;

	title = new QLabel(i18n("Labels"));
	layout->addWidget(title, 0, 0, 1, 1, Qt::AlignLeft);
	showBtn = new QPushButton(KIcon("arrow-down-double"), "");
	showBtn->setFlat(true);
	showBtn->setMaximumWidth(30);
	connect(showBtn, SIGNAL(clicked()), this, SLOT(toggleVisibility()));
	layout->addWidget(showBtn, 0, 1, 1, 1, Qt::AlignRight);

	list = new QListWidget;
	fillList();
	list->setVisible(false);
	list->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu()));
	layout->addWidget(list, 1, 0, 1, 2);

	setupActions();

	setLayout(layout);
}

LabelList::~LabelList()
{
	delete clearAction;
	delete addBannedLabelAction;
	delete addLabelAction;
	delete list;
	delete showBtn;
	delete title;
	delete layout;
}

void LabelList::fillList()
{
	list->clear();
	QStringList labels = Controller::create()->getDataStore()->getRootLabel()->toStringList();
	labels.removeOne("");
	labels = labels.toSet().toList(); // remove duplicates
	labels.sort();
	list->addItems(labels);
}

void LabelList::setupActions()
{

	addLabelAction = new QAction(i18n("Add Label"), this);
	addLabelAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
	addLabelAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	this->addAction(addLabelAction);
	connect(addLabelAction, SIGNAL(triggered()), this, SLOT(addLabel()));

	addBannedLabelAction = new QAction(i18n("Ban Label"), this);
	addBannedLabelAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
	addBannedLabelAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	this->addAction(addBannedLabelAction);
	connect(addBannedLabelAction, SIGNAL(triggered()), this, SLOT(addBannedLabel()));

	clearAction = new QAction(i18n("Clear Label"), this);
	clearAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
	clearAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
	this->addAction(clearAction);
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
}

void LabelList::update()
{
	fillList();
	emit clearLabels();
	emit clearBannedLabels();
}

void LabelList::toggleVisibility()
{
	if (showOptions)
	{
		showBtn->setIcon(KIcon("arrow-down-double"));
		showOptions = false;
	} else {
		showBtn->setIcon(KIcon("arrow-up-double"));
		showOptions = true;
	}
	list->setVisible(showOptions);
}

void LabelList::showContextMenu()
{
	QMenu menu(this);
	menu.addAction(addLabelAction);
	menu.addAction(addBannedLabelAction);
	menu.addAction(clearAction);
	menu.exec(QCursor::pos());
}

void LabelList::addLabel()
{
	if (list->selectedItems().isEmpty())
		return;
	QListWidgetItem *item = list->selectedItems().first();
	item->setIcon(KIcon("list-add"));
	emit removedBannedLabel(item->text());
	emit addedLabel(item->text());
}

void LabelList::addBannedLabel()
{
	if (list->selectedItems().isEmpty())
		return;
	QListWidgetItem *item = list->selectedItems().first();
	item->setIcon(KIcon("list-remove"));
	emit removedLabel(item->text());
	emit addedBannedLabel(item->text());
}

void LabelList::clear()
{
	if (list->selectedItems().isEmpty())
		return;
	QListWidgetItem *item = list->selectedItems().first();
	item->setIcon(KIcon());
	emit removedLabel(item->text());
	emit removedBannedLabel(item->text());
}





