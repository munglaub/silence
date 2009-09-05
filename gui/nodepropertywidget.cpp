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
#include "nodepropertywidget.h"


NodePropertyWidget::NodePropertyWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	layout = new QVBoxLayout;

	tabwidget = new QTabWidget(this);
	layout->addWidget(tabwidget);
	tabwidget->addTab(createNodeInfoTab(), tr("Nodeinfos"));
	tabwidget->addTab(createLabelTab(), tr("Labels"));

	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
}

NodePropertyWidget::~NodePropertyWidget()
{
	delete applyLabels;
	delete availlabels;
	delete btnAddLabel;
	delete newLabel;
	delete labellayout;
	delete labelframe;

	delete applyNodeInfo;
	delete syntax;
	delete modificationdate;
	delete creationdate;
	delete nodeName;
	delete infolayout;
	delete infoframe;
	
	delete tabwidget;
	delete layout;
	delete frame;
}

QWidget* NodePropertyWidget::createNodeInfoTab()
{
	infolayout = new QFormLayout;
	nodeName = new QLineEdit;
	infolayout->addRow(tr("Node name:"), nodeName);
	
	syntax = new QComboBox;
	syntax->addItem(tr("None"));
	syntax->addItem(tr("Bash"));
	syntax->addItem(tr("Batch"));
	syntax->addItem(tr("CMake"));
	syntax->addItem(tr("C++"));
	syntax->addItem(tr("C#"));
	syntax->addItem(tr("CSS"));
	syntax->addItem(tr("D"));
	syntax->addItem(tr("Diff"));
	syntax->addItem(tr("HTML"));
	syntax->addItem(tr("IDL"));
	syntax->addItem(tr("Java"));
	syntax->addItem(tr("JavaScript"));
	syntax->addItem(tr("Lua"));
	syntax->addItem(tr("Makefile"));
	syntax->addItem(tr("Perl"));
	syntax->addItem(tr("POV"));
	syntax->addItem(tr("Python"));
	syntax->addItem(tr("Ruby"));
	syntax->addItem(tr("SQL"));
	syntax->addItem(tr("TeX"));
	syntax->addItem(tr("VHDL"));
	infolayout->addRow(tr("Syntax:"), syntax);
	
	creationdate = new QLabel("");
	infolayout->addRow(tr("Creationdate:"), creationdate);

	modificationdate = new QLabel("");
	infolayout->addRow(tr("Modificationdate:"), modificationdate);

	applyNodeInfo = new QPushButton(tr("Apply"));
	infolayout->addRow("", applyNodeInfo);
	connect(applyNodeInfo, SIGNAL(clicked()), this, SLOT(saveNodeInfo()));

	infoframe = new QFrame;
	infoframe->setLayout(infolayout);
	return infoframe;
}

QWidget* NodePropertyWidget::createLabelTab()
{

	labellayout = new QGridLayout;
	newLabel = new QLineEdit;
	labellayout->addWidget(newLabel, 0, 0);
	btnAddLabel = new QPushButton(tr("Add"));
	connect(btnAddLabel, SIGNAL(clicked()), this, SLOT(addLabel()));
	labellayout->addWidget(btnAddLabel, 0, 1);
	availlabels = new QListWidget;
	availlabels->setSelectionMode(QAbstractItemView::MultiSelection);
	availlabels->addItems(*Controller::create()->getDataStore()->getLabels());
	labellayout->addWidget(availlabels, 1, 0, 1, 2);

	applyLabels = new QPushButton(tr("Apply"));
	connect(applyLabels, SIGNAL(clicked()), this, SLOT(saveLabels()));
	labellayout->addWidget(applyLabels, 2, 1);

	labelframe = new QFrame;
	labelframe->setLayout(labellayout);
	return labelframe;
}

void NodePropertyWidget::setNode(Node* node)
{
	// nodeinfos
	this->node = node;
	nodeName->setText(node->getCaption());
	syntax->setEnabled(false);
	if (node->getContent() != 0)
		if (node->getContent()->getMimeType() == "text/plain")
			syntax->setEnabled(true);

	creationdate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	modificationdate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));
	
	// labels
	availlabels->clear();
	QStringList *allLabels = Controller::create()->getDataStore()->getLabels();
	for (int i=0; i<allLabels->size(); ++i)
	{
		availlabels->addItem(allLabels->at(i));
		if (node->getLabels()->contains(allLabels->at(i)))
			availlabels->item(availlabels->count() - 1)->setSelected(true);
	}
}


void NodePropertyWidget::saveNodeInfo()
{
	node->setCaption(nodeName->text());
	if (syntax->isEnabled())
		node->getContent()->addMetaInfo("Syntax", syntax->currentText());
}

void NodePropertyWidget::saveLabels()
{
	node->getLabels()->clear();
	for (int i=0; i<availlabels->selectedItems().size(); ++i)
		node->addLabel(availlabels->selectedItems().at(i)->text());
}

void NodePropertyWidget::addLabel()
{
	if (newLabel->text().isEmpty())
		return;
	availlabels->addItem(newLabel->text());
	availlabels->item(availlabels->count() - 1)->setSelected(true);
	QStringList *labels = Controller::create()->getDataStore()->getLabels();
	if (!labels->contains(newLabel->text()))
		labels->append(newLabel->text());
}


