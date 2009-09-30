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

#include "gui/infosidebar.h"
#include <QGridLayout>
#include <QLabel>
#include <QWidget>


InfoSidebar::InfoSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	node = 0;

	int row = 0;

	caption = new QLabel("");
	caption->setWordWrap(true);
	caption->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(caption, row, 0, 1, 2, Qt::AlignCenter);
	++row;
	
	icon = new QLabel("");
	layout->addWidget(icon, row, 0, 1, 2, Qt::AlignCenter);
	++row;

	created = new QLabel(tr("Created:"));
	created->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(created, row, 0);
	createdDate = new QLabel("-");
	layout->addWidget(createdDate, row, 1);
	++row;

	lastedit = new QLabel(tr("Last edit:"));
	lastedit->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(lastedit, row, 0);
	lasteditDate = new QLabel("-");
	layout->addWidget(lasteditDate, row, 1);
	++row;

	type = new QLabel(tr("Type:"));
	type->setFont(QFont("Times", 10, QFont::Bold));
	type->setHidden(true);
	layout->addWidget(type, row, 0);
	typeName = new QLabel("");
	typeName->setHidden(true);
	layout->addWidget(typeName, row, 1);
	++row;

	labels = new QLabel(tr("Labels:"));
	labels->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(labels, row, 0);
	labelsData = new QLabel("-");
	labelsData->setWordWrap(true);
	layout->addWidget(labelsData, row, 1);
	++row;

	metaInfo = new QLabel("");
	metaInfo->setFont(QFont("Times", 10, QFont::Bold));
	layout->addWidget(metaInfo, row, 0);
	metaInfoData = new QLabel("");
	layout->addWidget(metaInfoData, row, 1);


	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
}

InfoSidebar::~InfoSidebar()
{
	delete icon;
	delete created;
	delete createdDate;
	delete lastedit;
	delete lasteditDate;
	delete labels;
	delete labelsData;
	delete metaInfo;
	delete metaInfoData;
	delete layout;
	delete frame;
}

void InfoSidebar::setData(Node *data)
{
	if (node != 0)
		disconnect(node, SIGNAL(changed(Node*)), this, SLOT(updateInfos()));
	node = data;
	if (node != 0)
		connect(node, SIGNAL(changed(Node*)), this, SLOT(updateInfos()));
	updateInfos();
}

void InfoSidebar::clearInfos()
{
	caption->setText("");
	createdDate->setText("-");
	lasteditDate->setText("-");
	labelsData->setText("-");
	icon->setPixmap(QPixmap());
	type->setHidden(true);
	typeName->setHidden(true);
	metaInfo->setHidden(true);
	metaInfoData->setHidden(true);
}

void InfoSidebar::updateInfos()
{
	if (node == 0)
	{
		return;
	}

	// set node infos
	caption->setText(node->getCaption());
	createdDate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	lasteditDate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));

	labelsData->setText(node->getLabels()->join(", "));

	// set content infos
	if (node->getContent())
	{
		icon->setPixmap(node->getContent()->getIcon().pixmap(64, 64));

		typeName->setText(node->getContent()->getMimeType());
		type->setHidden(false);
		typeName->setHidden(false);

		QString cap = "";
		QString inf = "";
		// metainfos
		QHashIterator<QString, QString> itr(*node->getContent()->getMetaInfos());
		while (itr.hasNext())
		{
			itr.next();
			cap += itr.key() + "\n";
			inf += itr.value() + "\n";
		}
		metaInfo->setText(cap);
		metaInfoData->setText(inf);
		metaInfo->setHidden(false);
		metaInfoData->setHidden(false);
	} else {
		type->setHidden(true);
		typeName->setHidden(true);
		metaInfo->setHidden(true);
		metaInfoData->setHidden(true);
	}
}

