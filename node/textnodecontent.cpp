#include "node/textnodecontent.h"
#include "gui/textedit.h"

#include<QLabel>

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
		icon = QIcon("icons/mimetype/64x64/application-javascript.png");
		pixmap = QPixmap("icons/mimetype/application-javascript.png");
		return;
	} 
	if (metaInfos->value("Syntax") == "Perl")
	{
		icon = QIcon("icons/mimetype/64x64/application-x-perl.png");
		pixmap = QPixmap("icons/mimetype/16x16/application-x-perl.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Ruby")
	{
		icon = QIcon("icons/mimetype/64x64/application-x-ruby.png");
		pixmap = QPixmap("icons/mimetype/16x16/application-x-ruby.png");
		return;
	}
	if (metaInfos->value("Syntax") == "CSS")
	{
		icon = QIcon("icons/mimetype/64x64/text-css.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-css.png");
		return;
	}
	if (metaInfos->value("Syntax") == "HTML")
	{
		icon = QIcon("icons/mimetype/64x64/text-html.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-html.png");
		return;
	}
	if (metaInfos->value("Syntax") == "CMake")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-cmake.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-cmake.png");
		return;
	}
	if (metaInfos->value("Syntax") == "C#")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-csharp.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-csharp.png");
		return;
	}
	if (metaInfos->value("Syntax") == "C++")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-c++src.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-c++src.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Java")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-java.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-java.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Makefile")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-makefile.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-makefile.png");
		return;
	}
	if (metaInfos->value("Syntax") == "Python")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-python.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-python.png");
		return;
	}
	if (metaInfos->value("Syntax") == "SQL")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-sql.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-sql.png");
		return;
	}
	if (metaInfos->value("Syntax") == "TeX")
	{
		icon = QIcon("icons/mimetype/64x64/text-x-tex.png");
		pixmap = QPixmap("icons/mimetype/16x16/text-x-tex.png");
		return;
	}
	icon = QIcon("icons/mimetype/64x64/text-plain.png");
	pixmap = QPixmap("icons/mimetype/16x16/text-plain.png");
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
	TextEdit *widget = TextEdit::create();
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


