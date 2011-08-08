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
	delete metaInfos;
}

AbstractContentView* BookNodeContent::getWidget()
{
	BookView *view = Controller::create()->getBookView();
	view->setHtmlContent(createContent());
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

bool BookNodeContent::contains(const QString&)
{
	return false;
}

QDomElement BookNodeContent::getXmlData(QDomDocument&)
{
	return QDomElement();
}

void BookNodeContent::setXmlData(QDomElement&)
{
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
	// TODO: not shure what to return..
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
		html += "<li><a href=\"#" + node->getChild(i)->getId().toString() + "\">"  + node->getChild(i)->getCaption() + "</a></li>";
		html = visitNodesForCaption(html, node->getChild(i));
	}
	html += "</ul>";
	return html;
}

QString BookNodeContent::visitNodesForContent(QString html, Node *node, QString &backlink)
{
	if (node->getChildCount() < 1)
		return html;
	for (int i=0; i < node->getChildCount(); ++i){
		Node *n = node->getChild(i);
		html += " - <a href=\"#" + n->getId().toString() + "\"> next (" + n->getCaption() + ")</a>";
		html += "</div>";
		html += "<hr>";
		QString nodeId = n->getId().toString();
		html += "<h2><a name=\"" + nodeId + "\" href=\"silence://0.0.0.0/" + nodeId + "\">"  + n->getCaption() + "</a></h2>";
		html += n->getContent()->getHtml();

		if (n->getContent()->getMimeType() != "silence/book"){
			QString navi = "<div align=\"center\">";
			navi += backlink;
			navi += "<a href=\"#top\">" + i18n("top") + "</a> ";
			html += navi;

			// backlink for the next node
			backlink = "<a href=\"#" + n->getId().toString() + "\"> back (" + n->getCaption() + ")</a> - ";
			html = visitNodesForContent(html, node->getChild(i), backlink);
		}
	}
	return html;
}

QString BookNodeContent::createContent()
{
	QString html = "<h1>" + this->node->getCaption() + "</h1>";
	html = visitNodesForCaption(html, this->node);
	QString backlink = "<a href=\"#" + this->node->getId().toString() + "\"> back (" + this->node->getCaption() + ")</a> - ";
	html += "<div align=\"center\">";
	html += "<a href=\"#top\">" + i18n("top") + "</a> ";
	html = visitNodesForContent(html, this->node, backlink);
	html += "</div>";
	return html;
}

QString BookNodeContent::getHtml()
{
	return createContent();
}

