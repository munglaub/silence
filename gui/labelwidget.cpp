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
	setupTree();
	setLayout(layout);
}

LabelWidget::~LabelWidget()
{
	delete newLabel;
	delete btnAddLabel;
	delete labeltree;
	delete layout;
}

void LabelWidget::setupTree()
{
	labeltree = new QTreeWidget;
	labeltree->setColumnCount(1);
	labeltree->setHeaderItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Label"))));
	labeltree->setSelectionMode(QAbstractItemView::MultiSelection);
	QStringList* labels = Controller::create()->getDataStore()->getLabels();
	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < labels->size(); ++i)
		items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(labels->at(i))));
	labeltree->insertTopLevelItems(0, items);
	layout->addWidget(labeltree, 1, 0, 1, 2);
}

void LabelWidget::addLabel()
{
	if (newLabel->text().isEmpty())
		return;

	QStringList *labels = Controller::create()->getDataStore()->getLabels();
	if (!labels->contains(newLabel->text()))
	{
		// add and select the new label
		labels->append(newLabel->text());
		QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(newLabel->text()));
		labeltree->insertTopLevelItem(labeltree->topLevelItemCount(), item);
		labeltree->setCurrentItem(item);
	} else {
		// select the existing label
		QList<QTreeWidgetItem *> items = labeltree->findItems(newLabel->text(), Qt::MatchExactly, 0);
		for (int i = 0; i < items.size(); ++i)
			labeltree->setCurrentItem(items.at(i));
	}
}

QStringList LabelWidget::getLabels() const
{
	int column = 0;
	QStringList result;
	for (int i = 0; i < labeltree->selectedItems().size(); ++i)
		result << labeltree->selectedItems().at(i)->text(column);
	return result;
}

void LabelWidget::selectLabels(QStringList select)
{
	labeltree->clear();
	QStringList* labels = Controller::create()->getDataStore()->getLabels();
	for (int i = 0; i < labels->size(); ++i)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(labels->at(i)));
		labeltree->insertTopLevelItem(0, item);
		if (select.contains(labels->at(i)))
			labeltree->setCurrentItem(item);
	}
}


