#include "node/textnodecontent.h"
#include "gui/textedit.h"

#include<QLabel>

TextNodeContent::TextNodeContent()
{
	text = "";
	metaInfos = new QHash<QString, QString>;
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

QString TextNodeContent::getMimeType()
{
	return "text/plain";
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



