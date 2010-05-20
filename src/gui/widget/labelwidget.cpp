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
#include "src/controller.h"
#include "src/gui/dialog/labelmanagementdialog.h"
#include "src/gui/widget/labelwidget.h"


LabelWidget::LabelWidget(QWidget *parent, bool showManageLabelsBtn)
	: QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setupTree();
	connect(labeltree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(itemActivated(QTreeWidgetItem*, int)));

	manageLabelsBtn = new QPushButton(i18n("Manage Labels"));
	manageLabelsBtn->setVisible(showManageLabelsBtn);
	connect(manageLabelsBtn, SIGNAL(clicked()), this, SLOT(manageLabels()));
	layout->addWidget(manageLabelsBtn, 0, 1, 1, 1, Qt::AlignTop);
	setLayout(layout);
}

LabelWidget::~LabelWidget()
{
	delete labeltree;
	delete manageLabelsBtn;
	delete layout;
}

void LabelWidget::setupTree()
{
	labeltree = new QTreeWidget;
	labeltree->setColumnCount(1);
	fillTree();
	layout->addWidget(labeltree, 0, 0, 1, 1);
}

void LabelWidget::fillTree()
{
	labeltree->clear();
	labeltree->setHeaderItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(i18n("Label")))));
	labeltree->setSelectionMode(QAbstractItemView::MultiSelection);

	Label* rootLabel = Controller::create()->getDataStore()->getRootLabel();
	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < rootLabel->childCount(); ++i)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(rootLabel->getChild(i)->getText()));
		items.append(item);
		addLabel(item, rootLabel->getChild(i));
	}
	labeltree->insertTopLevelItems(0, items);
	labeltree->expandAll();
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

void LabelWidget::itemActivated(QTreeWidgetItem *item, int)
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
	QSet<QString> result;
	for (int i = 0; i < labeltree->selectedItems().size(); ++i)
		result << labeltree->selectedItems().at(i)->text(column);
	return result.toList();
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

void LabelWidget::manageLabels()
{
	LabelManagementDialog *dlg = new LabelManagementDialog;
	dlg->exec();
	delete dlg;
	fillTree();
	Controller::create()->getNodePropertyWidget()->updateLabels();
	Controller::create()->getSearchNodeSidebar()->updateLabels();
}

void LabelWidget::updateLabels()
{
	fillTree();
}


