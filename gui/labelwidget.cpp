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
	//TODO: auch wenn das mit tastatur gemacht wird..
	connect(labeltree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(itemActivated(QTreeWidgetItem*, int)));
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

	Label* rootLabel = Controller::create()->getDataStore()->getLabels();
	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < rootLabel->childCount(); ++i)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(rootLabel->getChild(i)->getText()));
		items.append(item);
		addLabel(item, rootLabel->getChild(i));
	}
	labeltree->insertTopLevelItems(0, items);

	layout->addWidget(labeltree, 1, 0, 1, 2);
}

void LabelWidget::addLabel(QTreeWidgetItem* parent, Label* label)
{
	for (int i = 0; i < label->childCount(); ++i)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(label->getChild(i)->getText()));
		parent->addChild(item);
		addLabel(item, label->getChild(i));
	}
}

//TODO: muss glaube ich weg
void LabelWidget::addLabel()
{
	if (newLabel->text().isEmpty())
		return;

	Label* rootLabel = Controller::create()->getDataStore()->getLabels();
	rootLabel->appendChild(new Label(newLabel->text()));
	QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(newLabel->text()));
	labeltree->insertTopLevelItem(labeltree->topLevelItemCount(), item);
	labeltree->setCurrentItem(item);
	//TODO: die funktionalitaet wieder herstellen die schonmal da war..

/*
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
*/
}

void LabelWidget::itemActivated(QTreeWidgetItem *item, int column)
{
	if (item->isSelected())
	{
		// select all parents
		QTreeWidgetItem *p = item;
		while (p->parent())
		{
			p = p->parent();
			labeltree->setCurrentItem(p, 0, QItemSelectionModel::Select);
		}
	} else {
		// deselect all children
		deselectChildren(item);
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
	// clear selection
	labeltree->setCurrentItem(0, 0, QItemSelectionModel::Clear);
	// select the labels
	int column = 0;
	for (int j = 0; j < select.size(); ++j)
	{
		QList<QTreeWidgetItem *> items = labeltree->findItems(select.at(j), Qt::MatchRecursive, column);
		for (int i = 0; i < items.size(); ++i)
			labeltree->setCurrentItem(items.at(i));
	}
}

void LabelWidget::deselectChildren(QTreeWidgetItem* item)
{
	for (int i = 0; i < item->childCount(); ++i)
	{
		labeltree->setCurrentItem(item->child(i), 0, QItemSelectionModel::Deselect);
		deselectChildren(item->child(i));
	}
}

