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

#include "src/controller.h"
#include "src/data/node/textnodecontent.h"
#include "src/gui/view/textedit.h"
#include <KIcon>


TextNodeContent::TextNodeContent()
{
	text = "";
	metaInfos = new QHash<QString, QString>;
	
	setGraphics();
}

TextNodeContent::~TextNodeContent()
{
	delete metaInfos;
}

void TextNodeContent::setGraphics()
{
	if (metaInfos->value("Syntax") == "JavaScript")
	{
		icon = KIcon("application-javascript");
		return;
	} 
	if (metaInfos->value("Syntax") == "Perl")
	{
		icon = KIcon("application-x-perl");
		return;
	}
	if (metaInfos->value("Syntax") == "Ruby")
	{
		icon = KIcon("application-x-ruby");
		return;
	}
	if (metaInfos->value("Syntax") == "CSS")
	{
		icon = KIcon("text-css");
		return;
	}
	if (metaInfos->value("Syntax") == "HTML")
	{
		icon = KIcon("text-html");
		return;
	}
	if (metaInfos->value("Syntax") == "CMake")
	{
		icon = KIcon("text-x-cmake");
		return;
	}
	if (metaInfos->value("Syntax") == "C#")
	{
		icon = KIcon("text-x-csharp");
		return;
	}
	if (metaInfos->value("Syntax") == "C++")
	{
		icon = KIcon("text-x-c++src");
		return;
	}
	if (metaInfos->value("Syntax") == "Java")
	{
		icon = KIcon("text-x-java");
		return;
	}
	if (metaInfos->value("Syntax") == "Makefile")
	{
		icon = KIcon("text-x-makefile");
		return;
	}
	if (metaInfos->value("Syntax") == "Python")
	{
		icon = KIcon("text-x-python");
		return;
	}
	if (metaInfos->value("Syntax") == "SQL")
	{
		icon = KIcon("text-x-sql");
		return;
	}
	if (metaInfos->value("Syntax") == "TeX")
	{
		icon = KIcon("text-x-tex");
		return;
	}
	icon = KIcon("text-plain");
}

void TextNodeContent::setText(QString text)
{
	this->text = text;
	emit changed();
}

QString TextNodeContent::getText() const
{
	return text;
}

QWidget* TextNodeContent::getWidget()
{
	TextEdit *widget = Controller::create()->getTextEdit();
	widget->setContent(this);
	widget->setSyntax(metaInfos->value("Syntax"));
	return widget;
}

QHash<QString, QString>* TextNodeContent::getMetaInfos()
{
	return metaInfos;
}

void TextNodeContent::addMetaInfo(QString key, QString value)
{
	metaInfos->insert(key, value);
	if (key == "Syntax")
		setGraphics();
	emit changed();
}

QString TextNodeContent::getMimeType()
{
	return "text/plain";
}

bool TextNodeContent::contains(const QString& value)
{
	return text.contains(value, Qt::CaseInsensitive);
}

void TextNodeContent::setSyntax(QString syntax)
{
	metaInfos->insert("Syntax", syntax);
	setGraphics();
	emit changed();
}

QDomElement TextNodeContent::getXmlData(QDomDocument &doc)
{
	QDomElement text = doc.createElement("text");
	QDomText textData = doc.createTextNode(this->text);
	text.appendChild(textData);
	return text;
}

void TextNodeContent::setXmlData(QDomElement &xmlNode)
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
	setGraphics();
}

QPixmap TextNodeContent::getPixmap()
{
	return icon.pixmap(16, 16);
}

QIcon TextNodeContent::getIcon()
{
	return icon;
}

QString TextNodeContent::toString()
{
	QString result;

	result.append("Metainfos\n");
	QHashIterator<QString, QString> itr(*metaInfos);
	while (itr.hasNext())
	{
		itr.next();
		result.append("\t" + itr.key() + " :  " + itr.value() + "\n");
	}

	result.append("Text:\n");
	result.append(text);

	return result;
}


