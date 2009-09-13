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
#include "gui/textedit.h"
#include "node/textnodecontent.h"


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
		icon = QIcon(":/icons/mimetype_64px/application-javascript.png");
		pixmap = QPixmap(":/icons/mimetype_16px/application-javascript.png");
		return;
	} 
	if (metaInfos->value("Syntax") == "Perl")
	{
		icon = QIcon(":/icons/mimetype_64px/application-x-perl.png");
		pixmap = QPixmap(":/icons/mimetype_16px/application-x-perl.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Ruby")
	{
		icon = QIcon(":/icons/mimetype_64px/application-x-ruby.png");
		pixmap = QPixmap(":/icons/mimetype_16px/application-x-ruby.png");
		return;
	}
	if (metaInfos->value("Syntax") == "CSS")
	{
		icon = QIcon(":/icons/mimetype_64px/text-css.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-css.png");
		return;
	}
	if (metaInfos->value("Syntax") == "HTML")
	{
		icon = QIcon(":/icons/mimetype_64px/text-html.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-html.png");
		return;
	}
	if (metaInfos->value("Syntax") == "CMake")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-cmake.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-cmake.png");
		return;
	}
	if (metaInfos->value("Syntax") == "C#")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-csharp.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-csharp.png");
		return;
	}
	if (metaInfos->value("Syntax") == "C++")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-c++src.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-c++src.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Java")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-java.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-java.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Makefile")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-makefile.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-makefile.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Python")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-python.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-python.png");
		return;
	}
	if (metaInfos->value("Syntax") == "SQL")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-sql.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-sql.png");
		return;
	}
	if (metaInfos->value("Syntax") == "TeX")
	{
		icon = QIcon(":/icons/mimetype_64px/text-x-tex.png");
		pixmap = QPixmap(":/icons/mimetype_16px/text-x-tex.png");
		return;
	}
	icon = QIcon(":/icons/mimetype_64px/text-plain.png");
	pixmap = QPixmap(":/icons/mimetype_16px/text-plain.png");
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
	return text.contains(value);
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
	return pixmap;
}

QIcon TextNodeContent::getIcon()
{
	return icon;
}


