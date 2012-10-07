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

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "src/controller.h"
#include "src/data/node/booknodecontent.h"
#include "src/data/node/node.h"
#include "src/data/node/richtextnodecontent.h"
#include "src/persistence/kjotsimporter.h"

KjotsImporter::KjotsImporter(Node *node, QString fileName)
{
	this->rootNode = node;
	this->fileName = fileName;
}

KjotsImporter::~KjotsImporter()
{
}

void KjotsImporter::getBook(QDomElement element, Node *parentNode)
{
	int index = parentNode->getChildCount();
	parentNode->addChildren(index, 1);

	Node *node = parentNode->getChild(index);
	node->setId(new NodeId);
	node->setModificationDate(QDateTime::currentDateTime());
	node->setCreationDate(QDateTime::currentDateTime());
	node->setContent(new BookNodeContent);
	importedNodes << node;

	QDomNode n = element.firstChild();
	while (!n.isNull()){
		QDomElement e = n.toElement();
		if (e.tagName().toLower() == "title"){
			node->setCaption(e.text());
		}
		if (e.tagName().toLower() == "kjotsbook"){
			getBook(e, node);
		}
		if (e.tagName().toLower() == "kjotspage"){
			getPage(e, node);
		}
		n = n.nextSibling();
	}
	connect(node, SIGNAL(changed(Node*)), Controller::create()->getDataStore(), SLOT(saveNode(Node*)));
}

void KjotsImporter::getPage(QDomElement element, Node *parentNode)
{
	int index = parentNode->getChildCount();
	parentNode->addChildren(index, 1);
	Node *node = parentNode->getChild(index);
	node->setId(new NodeId());
	node->setModificationDate(QDateTime::currentDateTime());
	node->setCreationDate(QDateTime::currentDateTime());

	RichTextNodeContent *content = new RichTextNodeContent;
	node->setContent(content);
	importedNodes << node;

	QDomNode n = element.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName().toLower() == "title"){
			node->setCaption(e.text());
		} else if (e.tagName().toLower() == "text"){
			if (e.firstChild().isCDATASection()){
				QString text = e.firstChild().toCDATASection().data();
				content->setText(text);
			}
		}
		n = n.nextSibling();
	}
	connect(node, SIGNAL(changed(Node*)), Controller::create()->getDataStore(), SLOT(saveNode(Node*)));
}

QString KjotsImporter::readFile(QFile & file)
{
	QString xml = "";
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		// repair broken kjots xml
		line.replace("<KjotsBook>", "<kjotsbook>");
		line.replace("</KJotsBook>", "</kjotsbook>");
		line.replace("<KjotsPage>", "<kjotspage>");
		line.replace("</KJotsPage>", "</kjotspage>");
		xml += line + "\n";
	}
	return xml;
}

QList<Node*> KjotsImporter::import()
{
	QDomDocument doc;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)){
		return this->importedNodes;;
	}

	doc.setContent(readFile(file));
	file.close();

	QDomElement xmlRoot = doc.documentElement();
	if (xmlRoot.tagName().toLower() != "kjots"){
		return this->importedNodes;;
	}

	// needs to be saved/updated
	this->importedNodes << rootNode;

	QDomNode n = xmlRoot.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName().toLower() == "kjotsbook"){
			getBook(e, rootNode);
		}
		if (e.tagName().toLower() == "kjotspage"){
			getPage(e, rootNode);
		}
		n = n.nextSibling();
	}

	return this->importedNodes;
}

