/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <kglobalsettings.h>
#include <klocalizedstring.h>
#include "src/gui/sidebar/infosidebar.h"


InfoSidebar::InfoSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	setObjectName("InfoSidebar");
	layout = new QFormLayout;
	toplayout = new QVBoxLayout;
	node = 0;

	caption = new QLabel;
	caption->setWordWrap(true);
	QFont captionFont = caption->font();
	captionFont.setBold(true);
	caption->setFont(captionFont);
	toplayout->addWidget(caption, 0, Qt::AlignCenter);
	
	icon = new QLabel;
	toplayout->addWidget(icon, 0, Qt::AlignCenter);

	layout->addRow(toplayout);

	id = createInfoLabel(i18n("ID") + ':', true);
	idValue = createInfoLabel("-");
	layout->addRow(id, idValue);

	created = createInfoLabel(i18nc("time the node was created", "Created") + ':', true);
	createdDate = createInfoLabel("-");
	layout->addRow(created, createdDate);

	modified = createInfoLabel(i18nc("last time the node was modified", "Modified") + ':', true);
	modifiedDate = createInfoLabel("-");
	layout->addRow(modified, modifiedDate);

	type = createInfoLabel(i18n("Type") + ':', true);
	type->setHidden(true);
	typeName = createInfoLabel("");
	typeName->setHidden(true);
	layout->addRow(type, typeName);

	labels = createInfoLabel(i18n("Labels") + ':', true);
	labelsData = createInfoLabel("-");
	labelsData->setWordWrap(true);
	layout->addRow(labels, labelsData);

	metaInfo = createInfoLabel("", true);
	metaInfoData = createInfoLabel("");
	layout->addRow(metaInfo, metaInfoData);


	frame = new QFrame;
	frame->setLayout(layout);
	setWidget(frame);
}

InfoSidebar::~InfoSidebar()
{
	delete icon;
	delete id;
	delete idValue;
	delete created;
	delete createdDate;
	delete modified;
	delete modifiedDate;
	delete labels;
	delete labelsData;
	delete metaInfo;
	delete metaInfoData;
	delete toplayout;
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
	idValue->setText("-");
	createdDate->setText("-");
	modifiedDate->setText("-");
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
		clearInfos();
		return;
	}

	// set node information
	caption->setText(node->getCaption());
	idValue->setText(QString().setNum(node->getId().getId()));
	createdDate->setText(node->getCreationDate().toString(Qt::SystemLocaleShortDate));
	modifiedDate->setText(node->getModificationDate().toString(Qt::SystemLocaleShortDate));

	labelsData->setText(node->getLabels()->join(", "));

	// set content information
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
			cap += itr.key() + '\n';
			inf += itr.value() + '\n';
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

QLabel* InfoSidebar::createInfoLabel(QString text, bool caption)
{
	QLabel *label = new QLabel(text);
	if (caption)
	{
		QColor color = palette().color(QPalette::Foreground);
		color.setAlpha(128);
		QPalette labelPalette = label->palette();
		labelPalette.setColor(QPalette::Foreground, color);
		label->setPalette(labelPalette);
	}
	label->setFont(KGlobalSettings::smallestReadableFont());
	return label;
}


