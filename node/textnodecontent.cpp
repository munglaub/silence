#include "node/textnodecontent.h"
#include "gui/textedit.h"

#include<QLabel>

TextNodeContent::TextNodeContent()
{
	text = "ein wahnsinnig toller void text";
	metaInfos = new QHash<QString, QString>;
	metaInfos->insert("Syntax", "C++");
	metaInfos->insert("Licence", "None");
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
	//TODO: lexer abhaengig vom syntax metadingens setzen
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


