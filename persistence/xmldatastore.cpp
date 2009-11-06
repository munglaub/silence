/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
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

#include "persistence/xmldatastore.h"
#include "data/node/textnodecontent.h"
#include "data/node/richtextnodecontent.h"
#include <QFile>
#include <QTextStream>


// Constant for Datastore file
const QString XmlDataStore::DATA_FILE("data.xml");


XmlDataStore::XmlDataStore()
{
	rootNode = new Node();
	rootNode->setCaption(tr("Title")); // treecaption

	rootLabel = new Label(tr("Label"));

	QDomDocument doc;
	QFile file(DATA_FILE);
	if (!file.open(QIODevice::ReadOnly))
		return;
	doc.setContent(&file);
	file.close();
	
	QDomElement xmlRoot = doc.documentElement();
	if (xmlRoot.tagName() != "silence")
		return;
	QDomNode n = xmlRoot.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName() == "labels")
			xmlToLabels(e, rootLabel);
		if (e.tagName() == "node")
			xmlToNode(rootNode, n, doc);
		n = n.nextSibling();
	}
}

XmlDataStore::~XmlDataStore()
{
	//delete root; // not necessary, is done in the treemodel
	delete rootLabel;
}

Node* XmlDataStore::getRootNode()
{
	return rootNode;
}

Label* XmlDataStore::getRootLabel()
{
	return rootLabel;
}

void XmlDataStore::xmlToLabels(QDomElement &xmlLabels, Label* label)
{
	QDomNode n = xmlLabels.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName() == "label")
		{
			Label *newLabel = new Label(e.attribute("text", ""));
			label->appendChild(newLabel);
			xmlToLabels(e, newLabel);
		}
		n = n.nextSibling();
	}
}

void XmlDataStore::xmlToNode(Node* parentNode, QDomNode &xmlNode, QDomDocument &doc)
{
	// node erstellen
	int index = parentNode->getChildCount();
	if (!parentNode->addChildren(index, 1))
		return; // TODO: real solution
	Node *node = parentNode->getChild(index);
	
	node->setId(NodeId(xmlNode.toElement().attribute("id", "-1").toInt()));

	QDateTime modificationDate = QDateTime::currentDateTime();

	QDomNode n = xmlNode.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName() == "caption")
			node->setCaption(e.text());
		if (e.tagName() == "creationdate")
			node->setCreationDate(QDateTime::fromString(e.text()));
		if (e.tagName() == "modificationdate")
			modificationDate = QDateTime::fromString(e.text());
		if (e.tagName() == "label")
			node->addLabel(e.text());
		if (e.tagName() == "content")
		{
			if (e.attribute("mimetype", "") == "text/plain")
			{
				TextNodeContent *content = new TextNodeContent;
				content->setXmlData(e);
				node->setContent(content);
			}
			if (e.attribute("mimetype", "") == "text/richtext")
			{
				RichTextNodeContent *content = new RichTextNodeContent;
				content->setXmlData(e);
				node->setContent(content);
			}
		}

		if (e.tagName() == "node")
			xmlToNode(node, n, doc);

		n = n.nextSibling();
	}
	node->setModificationDate(modificationDate);
	
	connect(node, SIGNAL(changed(Node*)), this, SLOT(saveNode(Node*)));
}

void XmlDataStore::saveNode(Node*)
{
	saveAll();
}

void XmlDataStore::saveAll()
{
	// create xmlDocument
	QDomDocument doc;
	doc.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"));
	QDomElement xmlRoot = doc.createElement("silence");
	doc.appendChild(xmlRoot);

	// write labels
	QDomElement xmlLabels = doc.createElement("labels");
	writeLabels(doc, xmlLabels, rootLabel);
	xmlRoot.appendChild(xmlLabels);

	// write nodes
	for (int i = 0; i < rootNode->getChildCount(); ++i)
	{
		addXmlNode(rootNode->getChild(i), xmlRoot, doc);
	}
	
	// write to file
	QFile file(DATA_FILE);
	if( !file.open(QIODevice::WriteOnly))
		return;
	QTextStream ts(&file);
	ts << doc.toString();
	file.close();
}

void XmlDataStore::writeLabels(QDomDocument &doc, QDomElement &parent, Label* parentLabel)
{
	for (int i = 0; i < parentLabel->childCount(); ++i)
	{
		QDomElement l = doc.createElement("label");
		l.setAttribute("text", parentLabel->getChild(i)->getText());
		parent.appendChild(l);
		writeLabels(doc, l, parentLabel->getChild(i));
	}
}

void XmlDataStore::addXmlNode(Node* node, QDomElement &parent, QDomDocument &doc)
{
	// node tag with id
	QDomElement xmlNode = doc.createElement("node");
	xmlNode.setAttribute("id", node->getId().getId());
	parent.appendChild(xmlNode);

	// caption
	QDomElement caption = doc.createElement("caption");
	QDomText captionText = doc.createTextNode(node->getCaption());
	caption.appendChild(captionText);
	xmlNode.appendChild(caption);

	// creationdate
	QDomElement cDate = doc.createElement("creationdate");
	QDomText cDateText = doc.createTextNode(node->getCreationDate().toString());
	cDate.appendChild(cDateText);
	xmlNode.appendChild(cDate);

	// modificationdate
	QDomElement mDate = doc.createElement("modificationdate");
	QDomText mDateText = doc.createTextNode(node->getModificationDate().toString());
	mDate.appendChild(mDateText);
	xmlNode.appendChild(mDate);

	// labels
	for (int i = 0; i < node->getLabels()->size(); ++i)
	{
		QDomElement label = doc.createElement("label");
		QDomText labelText = doc.createTextNode(node->getLabels()->at(i));
		label.appendChild(labelText);
		xmlNode.appendChild(label);
	}

	if (node->getContent())
	{
		// content with mimetype
		QDomElement content = doc.createElement("content");
		content.setAttribute("mimetype", node->getContent()->getMimeType());
		// metainfos
		QHashIterator<QString, QString> itr(*node->getContent()->getMetaInfos());
		while (itr.hasNext())
		{
			itr.next();
			QDomElement meta = doc.createElement("metainfo");
			meta.setAttribute("key", itr.key());
			QDomText metaValue = doc.createTextNode(itr.value());
			meta.appendChild(metaValue);
			content.appendChild(meta);
		}
		// contentdata
		content.appendChild(node->getContent()->getXmlData(doc));
		xmlNode.appendChild(content);
	}

	// children
	for (int i = 0; i < node->getChildCount(); ++i)
	{
		addXmlNode(node->getChild(i), xmlNode, doc);
	}
}

void XmlDataStore::removeNode(Node*)
{
	saveAll();
}

void XmlDataStore::addNode(Node*)
{
	saveAll();
}

void XmlDataStore::addLabel(Label*)
{
	saveAll();
}

void XmlDataStore::removeLabel(Label*)
{
	saveAll();
}



