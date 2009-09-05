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

#include "node/richtextnodecontent.h"
#include "gui/richtextedit.h"

RichTextNodeContent::RichTextNodeContent()
{
	text = "";
	metaInfos = new QHash<QString, QString>;
	icon = QIcon("icons/mimetype/64x64/text-rtf.png");
	pixmap = QPixmap("icons/mimetype/16x16/text-rtf.png");
}

RichTextNodeContent::~RichTextNodeContent()
{
	delete metaInfos;
}

QWidget* RichTextNodeContent::getWidget()
{
	RichTextEdit *widget = RichTextEdit::create();
	widget->setContent(this);
	return widget;
}

QHash<QString, QString>* RichTextNodeContent::getMetaInfos()
{
	return metaInfos;
}

void RichTextNodeContent::addMetaInfo(QString key, QString value)
{
	metaInfos->insert(key, value);
	emit changed();
}

QString RichTextNodeContent::getMimeType()
{
	return "text/richtext";
}

void RichTextNodeContent::setText(QString text)
{
	this->text = text;
	emit changed();
}

QString RichTextNodeContent::getText() const
{
	return text;
}

QDomElement RichTextNodeContent::getXmlData(QDomDocument &doc)
{
	QDomElement text = doc.createElement("text");
	QDomText textData = doc.createTextNode(this->text);
	text.appendChild(textData);
	return text;
}

void RichTextNodeContent::setXmlData(QDomElement &xmlNode)
{
	QDomNode n = xmlNode.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		
		if (e.tagName() == "metainfo")
			metaInfos->insert(e.attribute("key"), e.text());
		if (e.tagName() == "text")
			text = e.text();
			
		n = n.nextSibling();
	}
}

QPixmap RichTextNodeContent::getPixmap()
{
	return pixmap;
}

QIcon RichTextNodeContent::getIcon()
{
	return icon;
}

