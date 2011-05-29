/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/gui/dialog/saveexitdialog.h"
#include <klocalizedstring.h>
#include <QStringList>
#include "src/controller.h"


SaveExitDialog::SaveExitDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setupGui();
	addUnsavedNodes();
}

SaveExitDialog::~SaveExitDialog()
{
	// TODO: implement
}

void SaveExitDialog::setupGui(){
	setWindowTitle(i18n("Save Nodes"));

	layout = new QVBoxLayout;
	QLabel *info = new QLabel(i18n("The following nodes have been modified. Do you want to save them before closing?"));
	layout->addWidget(info);

	list = new QTreeWidget;
	list->setHeaderLabel(i18n("Title"));
	layout->addWidget(list);

	btnLayout = new QHBoxLayout;
	btnLayout->setAlignment(Qt::AlignRight);

	btnDontSave = new QPushButton(i18n("Do Not Save"));
	connect(btnDontSave, SIGNAL(clicked()), this, SLOT(accept()));
	btnLayout->addWidget(btnDontSave);
	
	btnSave = new QPushButton(i18n("Save Selected"));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));
	btnLayout->addWidget(btnSave);
	
	btnDontClose = new QPushButton(i18n("Do Not Close"));
	connect(btnDontClose, SIGNAL(clicked()), this, SLOT(reject()));
	btnLayout->addWidget(btnDontClose);
	
	layout->addLayout(btnLayout);
	setLayout(layout);
}

void SaveExitDialog::addUnsavedNodes()
{
	int column = 0;
	QList<Node*> nodes = Controller::create()->getChangeManager()->getNodes();
	for (int i=0; i<nodes.size(); ++i){
		QTreeWidgetItem *item = new QTreeWidgetItem(list);
		item->setText(column, nodes.at(i)->getCaption());
		item->setCheckState(column, Qt::Checked);
		list->addTopLevelItem(item);
		this->items.insert(item, nodes.at(i));
	}
}

void SaveExitDialog::save()
{
	QList<Node*> toSave;
	QHashIterator<QTreeWidgetItem*, Node*> i(this->items);
	int column = 0;
	while (i.hasNext()){
		i.next();
		if (i.key()->checkState(column) == Qt::Checked)
			toSave.append(i.value());
	}
	Controller::create()->getChangeManager()->saveNodes(toSave);

	accept();
}



