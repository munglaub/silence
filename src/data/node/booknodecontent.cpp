/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/data/node/booknodecontent.h"
#include "src/gui/view/bookview.h"


BookNodeContent::BookNodeContent()
{
	this->metaInfos = new QHash<QString, QString>;
}

BookNodeContent::~BookNodeContent()
{
	// TODO: implement
}

AbstractContentView* BookNodeContent::getWidget()
{
	BookView *view = Controller::create()->getBookView();
	view->setHtmlContent(createContent().arg("").arg(""));
	return view;
}

QHash<QString, QString>* BookNodeContent::getMetaInfos()
{
	return this->metaInfos;
}

void BookNodeContent::addMetaInfo(QString key, QString value)
{
	this->metaInfos->insert(key, value);
	emit changed();
}

QString BookNodeContent::getMimeType()
{
	return "silence/book";
}

bool BookNodeContent::contains(const QString& value)
{
	return false;
}

QDomElement BookNodeContent::getXmlData(QDomDocument &doc)
{
	// TODO: implement
	// im prinziep hat das ding ja keinen inhalt..
	return QDomElement();
}

void BookNodeContent::setXmlData(QDomElement &xmlNode)
{
	// TODO: implement
	// im prinziep hat das ding ja keinen inhalt..
}

QPixmap BookNodeContent::getPixmap()
{
	return getIcon().pixmap(16, 16);
}

QIcon BookNodeContent::getIcon()
{
	return KIcon("x-office-address-book");
}

QString BookNodeContent::toString()
{
	// TODO: implement
	// summe der ganzen nodes??
	return "";
}

void BookNodeContent::setParentNode(Node* parent)
{
	this->node = parent;
}

QString BookNodeContent::visitNodesForCaption(QString html, Node *node)
{
	if (node->getChildCount() < 1)
		return html;
	html += "<ul>";
	for (int i=0; i < node->getChildCount(); ++i){
		html += "<li><a href=\"#" + *(node->getChild(i)->getId().toString()) + "\">"  + node->getChild(i)->getCaption() + "</a></li>";
		html = visitNodesForCaption(html, node->getChild(i));
	}
	html += "</ul>";
	return html;
}

QString BookNodeContent::visitNodesForContent(QString html, Node *node)
{
	if (node->getChildCount() < 1)
		return html;
	for (int i=0; i < node->getChildCount(); ++i){
		Node *n = node->getChild(i);
		html += "<hr>";
		QString nodeId = *(n->getId().toString());
		html += "<h2><a name=\"" + nodeId + "\" href=\"silence://0.0.0.0/" + nodeId + "\">"  + n->getCaption() + "</a></h2>";
		html += n->getContent()->getHtml();

		if (n->getContent()->getMimeType() != "silence/book"){
			html = html.arg("#" + QString::number(n->getId().getId()));
			html = html.arg(n->getCaption());
			QString navi = "<div align=\"center\">";
			navi += "<a href=\"\">back</a> "; //TODO: name and link to the previous node
			navi += "<a href=\"#" + QString::number(this->node->getId().getId()) + "\">" + i18n("top") + "</a> ";
			navi += "<a href=\"%1\">%2</a>";
			navi += "</div>";
			html += navi;

			html = visitNodesForContent(html, node->getChild(i));
		}
	}
	return html;
}

QString BookNodeContent::createContent()
{
	QString html = "<h1><a name=\"" + QString::number(this->node->getId().getId()) + "\">" + this->node->getCaption() + "</a></h1>";
	html = visitNodesForCaption(html, this->node);
	html = visitNodesForContent(html, this->node);
	return html;
}

QString BookNodeContent::getHtml()
{
	return createContent();
}

