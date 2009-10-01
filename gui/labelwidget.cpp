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

#include "controller.h"
#include "gui/labelwidget.h"


LabelWidget::LabelWidget(QWidget *parent)
	: QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	newLabel = new QLineEdit;
	layout->addWidget(newLabel, 0, 0);
	btnAddLabel = new QPushButton(tr("Add"));
	connect(btnAddLabel, SIGNAL(clicked()), this, SLOT(addLabel()));
	layout->addWidget(btnAddLabel, 0, 1);
	availlabels = new QListWidget;
	availlabels->setSelectionMode(QAbstractItemView::MultiSelection);
	availlabels->addItems(*Controller::create()->getDataStore()->getLabels());
	layout->addWidget(availlabels, 1, 0, 1, 2);
	setLayout(layout);
}

LabelWidget::~LabelWidget()
{
	delete newLabel;
	delete btnAddLabel;
	delete availlabels;
	delete layout;
}

void LabelWidget::addLabel()
{
	if (newLabel->text().isEmpty())
		return;
	availlabels->addItem(newLabel->text());
	availlabels->item(availlabels->count() - 1)->setSelected(true);
	QStringList *labels = Controller::create()->getDataStore()->getLabels();
	if (!labels->contains(newLabel->text()))
		labels->append(newLabel->text());
}

QStringList LabelWidget::getLabels() const
{
	QStringList result;
	for (int i = 0; i < availlabels->selectedItems().size(); ++i)
		result << availlabels->selectedItems().at(i)->text();

	return result;
}

void LabelWidget::selectLabels(QStringList select)
{
	availlabels->clear();
	QStringList *allLabels = Controller::create()->getDataStore()->getLabels();
	for (int i=0; i<allLabels->size(); ++i)
	{
		availlabels->addItem(allLabels->at(i));
		if (select.contains(allLabels->at(i)))
			availlabels->item(availlabels->count() - 1)->setSelected(true);
	}
}


