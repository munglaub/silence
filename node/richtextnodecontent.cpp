#include "node/richtextnodecontent.h"
#include "gui/richtextedit.h"

RichTextNodeContent::RichTextNodeContent()
{
	text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /><style type=\"text/css\">	p, li { white-space: pre-wrap; }	</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">	<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600;\">RichTextEdit</span></p>	<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>	<ul style=\"-qt-list-indent: 1;\"><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ganz toll</li>	<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Monospace'; font-style:italic; color:#ff0000;\">wirklich</span></li></ul></body></html>";

	metaInfos = new QHash<QString, QString>;
	metaInfos->insert("Author", "foobar");
	metaInfos->insert("foo?", "Foobar!");
	metaInfos->insert("?", "!");
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

QString RichTextNodeContent::getMimeType()
{
	return "text/richtext";
}

void RichTextNodeContent::setText(QString text)
{
	this->text = text;
}

QString RichTextNodeContent::getText() const
{
	return text;
}


