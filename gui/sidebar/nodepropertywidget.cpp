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
#include "gui/sidebar/nodepropertywidget.h"


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
	delete labelwidget;
	delete labellayout;
	delete labelframe;

	delete applyNodeInfo;
	delete syntaxbox;
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
	
	syntaxbox = new SyntaxBox(false);
	infolayout->addRow(tr("Syntax:"), syntaxbox);
	
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
	labelwidget = new LabelWidget(this, false);
	labellayout->addWidget(labelwidget, 0, 0, 1, 2);

	applyLabels = new QPushButton(tr("Apply"));
	connect(applyLabels, SIGNAL(clicked()), this, SLOT(saveLabels()));
	labellayout->addWidget(applyLabels, 2, 1);

	labelframe = new QFrame;
	labelframe->setLayout(labellayout);
	return labelframe;
}

void NodePropertyWidget::setNode(Node* node)
{
	if (!node)
		return;
	// nodeinfos
	this->node = node;
	nodeName->setText(node->getCaption());
	syntaxbox->setEnabled(false);
	if (node->getContent() != 0)
		if (node->getContent()->getMimeType() == "text/plain")
		{
			syntaxbox->setEnabled(true);
			syntaxbox->setSyntax(node->getContent()->getMetaInfos()->value("Syntax"));
		}

	creationdate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	modificationdate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));
	
	// labels
	labelwidget->selectLabels(*node->getLabels());
}


void NodePropertyWidget::saveNodeInfo()
{
	node->setCaption(nodeName->text());
	if (syntaxbox->isEnabled())
		node->getContent()->addMetaInfo("Syntax", syntaxbox->getSyntax());
}

void NodePropertyWidget::saveLabels()
{
	node->getLabels()->clear();
	for (int i=0; i<labelwidget->getLabels().size(); ++i)
		node->addLabel(labelwidget->getLabels().at(i));
}

void NodePropertyWidget::updateLabels()
{
	labelwidget->updateLabels();
	setNode(node);
}

