#include "node/textnodecontent.h"
#include "gui/textedit.h"

#include<QLabel>

TextNodeContent::TextNodeContent()
{
	text = "ein wahnsinnig toller void text";
	widget = TextEdit::create();
	metaInfos = new QHash<QString, QString>;
	metaInfos->insert("Syntax", "C++");
	metaInfos->insert("Licence", "None");
}

TextNodeContent::~TextNodeContent()
{
	delete widget;
	delete metaInfos;
}

void TextNodeContent::setText(QString &text)
{
	this->text = text;
}

QString TextNodeContent::getText() const
{
	return text;
}


QWidget* TextNodeContent::getWidget()
{
	widget->setText(text);
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


