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

#include "src/controller.h"
#include "src/data/node/textnodecontent.h"
#include "src/gui/view/textedit.h"
#include <KIcon>


TextNodeContent::TextNodeContent()
{
	text = "";
	metaInfos = new QHash<QString, QString>;
	metaInfos->insert("Syntax", "None");
}

TextNodeContent::~TextNodeContent()
{
	delete metaInfos;
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

AbstractContentView* TextNodeContent::getWidget()
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
}

QPixmap TextNodeContent::getPixmap()
{
	return getIcon().pixmap(16, 16);
}

QIcon TextNodeContent::getIcon()
{
	if (metaInfos->value("Syntax") == "None")
		return KIcon("text-plain");
	if (metaInfos->value("Syntax") == "JavaScript")
		return KIcon("application-javascript");
	if (metaInfos->value("Syntax") == "Perl")
		return KIcon("application-x-perl");
	if (metaInfos->value("Syntax") == "Ruby")
		return KIcon("application-x-ruby");
	if (metaInfos->value("Syntax") == "CSS")
		return KIcon("text-css");
	if (metaInfos->value("Syntax") == "HTML")
		return KIcon("text-html");
	if (metaInfos->value("Syntax") == "CMake")
		return KIcon("text-x-cmake");
	if (metaInfos->value("Syntax") == "C#")
		return KIcon("text-x-csharp");
	if (metaInfos->value("Syntax") == "C++")
		return KIcon("text-x-c++src");
	if (metaInfos->value("Syntax") == "Java")
		return KIcon("text-x-java");
	if (metaInfos->value("Syntax") == "Makefile")
		return KIcon("text-x-makefile");
	if (metaInfos->value("Syntax") == "Python")
		return KIcon("text-x-python");
	if (metaInfos->value("Syntax") == "SQL")
		return KIcon("text-x-sql");
	if (metaInfos->value("Syntax") == "LaTeX")
		return KIcon("text-x-tex");
	if (metaInfos->value("Syntax") == "BibTeX")
		return KIcon("text-x-bibtex");
	if (metaInfos->value("Syntax") == "PHP (HTML)")
		return KIcon("application-x-php");
	if (metaInfos->value("Syntax") == "XML")
		return KIcon("application-xml");
	if (metaInfos->value("Syntax") == "Pascal")
		return KIcon("text-x-pascal");
	return KIcon("text-plain");
}

QString TextNodeContent::toString()
{
	QString result;

	result.append("Metainfos\n");
	QHashIterator<QString, QString> itr(*metaInfos);
	while (itr.hasNext())
	{
		itr.next();
		result.append('\t' + itr.key() + " :  " + itr.value() + '\n');
	}

	result.append("Text:\n");
	result.append(text);

	return result;
}


