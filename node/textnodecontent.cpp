#include "node/textnodecontent.h"

#include<QLabel>

TextNodeContent::TextNodeContent()
{
	widget = new QLabel("textwidget");
	metaInfos = new QHash<QString, QString>;
	metaInfos->insert("Syntax", "C++");
	metaInfos->insert("Licence", "None");
}

TextNodeContent::~TextNodeContent()
{
	delete widget;
	delete metaInfos;
}

QWidget* TextNodeContent::getWidget()
{
	return widget;
}

QHash<QString, QString>* TextNodeContent::getMetaInfos()
{
	return metaInfos;
}

