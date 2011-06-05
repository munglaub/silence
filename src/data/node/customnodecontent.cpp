/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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
#include "src/controller.h"
#include "src/data/node/customnodecontent.h"
#include "src/gui/view/customcontentview.h"


CustomNodeContent::CustomNodeContent(CustomNodeTypeDefinition *typeDefinition)
{
	init("silence/" + typeDefinition->getName());

	QListIterator<CustomNodeItem*> i(typeDefinition->getItemList());
	while (i.hasNext())
	{
		CustomNodeItem *item = new CustomNodeItem(i.peekNext()->getCaption(), i.peekNext()->getType());
		connect(item, SIGNAL(changed()), this, SLOT(onChange()));
		items.append(item);
		i.next();
	}

}
CustomNodeContent::CustomNodeContent(QString mimetype)
{
	init(mimetype);
}

CustomNodeContent::~CustomNodeContent()
{
	while (!items.isEmpty())
		delete items.takeFirst();
	delete metaInfos;
}

void CustomNodeContent::init(QString mimetype)
{
	this->mimetype = mimetype;
	metaInfos = new QHash<QString, QString>;
}

AbstractContentView* CustomNodeContent::getWidget()
{
	CustomContentView *view = Controller::create()->getCustomContentView();
	view->setItems(items);
	return view;
}

QHash<QString, QString>* CustomNodeContent::getMetaInfos()
{
	return metaInfos;
}

void CustomNodeContent::addMetaInfo(QString key, QString value)
{
	metaInfos->insert(key, value);
	emit changed();
}

QString CustomNodeContent::getMimeType()
{
	return mimetype;
}

bool CustomNodeContent::contains(const QString& value)
{
	bool contains = false;
	for (int i = 0; i < items.size() && !contains; ++i)
		contains = items.at(i)->getData().contains(value, Qt::CaseInsensitive);
	return contains;
}

QDomElement CustomNodeContent::getXmlData(QDomDocument &doc)
{
	QDomElement contentItems = doc.createElement("ContentItems");
	for (int i = 0; i < items.size(); ++i)
	{
		QDomElement item = doc.createElement("NodeItem");
		item.setAttribute("Type", QString::number(items.at(i)->getType()));
		item.setAttribute("Caption", items.at(i)->getCaption());
		QDomText data = doc.createTextNode(items.at(i)->getData());
		item.appendChild(data);

		contentItems.appendChild(item);
	}
	return contentItems;
}

void CustomNodeContent::setXmlData(QDomElement &xmlNode)
{
	QDomNode n = xmlNode.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();

		if (e.tagName() == "metainfo")
			metaInfos->insert(e.attribute("key"), e.text());
		if (e.tagName() == "ContentItems")
			readXmlContentItems(e);

		n = n.nextSibling();
	}
}

void CustomNodeContent::readXmlContentItems(QDomElement &xmlNode)
{
	while (!items.isEmpty())
		delete items.takeFirst();

	QDomNode n = xmlNode.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName() == "NodeItem")
		{
			CustomNodeItem *item = new CustomNodeItem(
				e.attribute("Caption", ""),
				(CustomNodeItem::Type)e.attribute("Type", "0").toInt()
			);
			item->setData(e.text());
			connect(item, SIGNAL(changed()), this, SLOT(onChange()));
			items.append(item);
		}
		n = n.nextSibling();
	}
}

QPixmap CustomNodeContent::getPixmap()
{
	return getIcon().pixmap(16, 16);
}

QIcon CustomNodeContent::getIcon()
{
	return KIcon("unknown");
}

QString CustomNodeContent::toString()
{
	// TODO: implement
	return "";
}

void CustomNodeContent::onChange()
{
	emit changed();
}

void CustomNodeContent::setParentNode(Node*)
{
}

QString CustomNodeContent::getHtml()
{
	//TODO: implement
	return "";
}



