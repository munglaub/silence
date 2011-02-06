/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include <ksavefile.h>
#include <kstandarddirs.h>
#include <QTextStream>
#include "src/controller.h"
#include "src/data/node/customnodecontent.h"
#include "src/data/node/richtextnodecontent.h"
#include "src/data/node/textnodecontent.h"
#include "src/persistence/xmldatastore.h"


// Constants for Datastore files
const QString XmlDataStore::DATA_FILE("silence/data.xml");
const QString XmlDataStore::TYPE_FILE("silence/customnodetypedefinitions.xml");


XmlDataStore::XmlDataStore()
{
	rootNode = new Node();

	rootLabel = new Label();

	loadCustomNodeTypeDefinitions();

	QDomDocument doc;
	QFile file(KStandardDirs::locateLocal("data", DATA_FILE));
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
			xmlToNode(rootNode, n, doc, this);
		n = n.nextSibling();
	}
}

XmlDataStore::~XmlDataStore()
{
	while(!customNodeTypeDefinitions.keys().isEmpty())
		delete customNodeTypeDefinitions.take(customNodeTypeDefinitions.keys().first());
	delete rootNode;
	delete rootLabel;
}

Node* XmlDataStore::getRootNode()
{
	return rootNode;
}

QStringList XmlDataStore::getCustomNodeTypeNames()
{
	return QStringList(customNodeTypeDefinitions.keys());
}

CustomNodeTypeDefinition* XmlDataStore::getCustomNodeType(QString name)
{
	if (customNodeTypeDefinitions.contains(name))
		return customNodeTypeDefinitions[name];
	else
		customNodeTypeDefinitions[name] = new CustomNodeTypeDefinition(name);
		saveCustomNodeTypeDefinitions();
		return customNodeTypeDefinitions[name];
}

void XmlDataStore::removeCustomNodeType(QString typeName)
{
	delete customNodeTypeDefinitions.take(typeName);
	saveCustomNodeTypeDefinitions();
}

void XmlDataStore::saveCustomNodeType(CustomNodeTypeDefinition *type)
{
	if (!customNodeTypeDefinitions.contains(type->getName()))
		customNodeTypeDefinitions[type->getName()] = type;
	saveCustomNodeTypeDefinitions();
}

Node* XmlDataStore::getNode(NodeId id)
{
	return findNode(rootNode, id);
}

Node* XmlDataStore::findNode(Node* parent, NodeId id)
{
	for (int i = 0; i < parent->getChildCount(); ++i)
	{
		if (parent->getChild(i)->getId().getId() == id.getId())
		{
			return parent->getChild(i);
		} else {
			Node *res = findNode(parent->getChild(i), id);
			if (res)
				return res;
		}
	}
	return 0;
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

void XmlDataStore::xmlToNode(Node* parentNode, QDomNode &xmlNode, QDomDocument &doc, AbstractDataStore *datastore)
{
	// node erstellen
	int index = parentNode->getChildCount();
	if (!parentNode->addChildren(index, 1))
		return; // TODO: real solution
	Node *node = parentNode->getChild(index);
	
	node->setId(new NodeId(xmlNode.toElement().attribute("id", "-1").toInt()));

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
			if (e.attribute("mimetype", "").startsWith("silence/"))
			{
				CustomNodeContent *content = new CustomNodeContent(e.attribute("mimetype", ""));
				content->setXmlData(e);
				node->setContent(content);
			}
		}

		if (e.tagName() == "node")
			xmlToNode(node, n, doc, datastore);

		n = n.nextSibling();
	}
	node->setModificationDate(modificationDate);
	
	connect(node, SIGNAL(changed(Node*)), datastore, SLOT(saveNode(Node*)));
}

void XmlDataStore::saveNode(Node*)
{
	saveAll();
}

void XmlDataStore::saveCustomNodeTypeDefinitions()
{
	QDomDocument doc;
	doc.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"));
	QDomElement xmlRoot = doc.createElement("CustomNodeTypeDefinitions");
	xmlRoot.setAttribute("version", "1");
	doc.appendChild(xmlRoot);

	QHashIterator<QString, CustomNodeTypeDefinition*> i(customNodeTypeDefinitions);
	while (i.hasNext())
	{
		i.next();

		QDomElement l = doc.createElement("TypeDefinition");
		l.setAttribute("name", i.value()->getName());
		QList<CustomNodeItem*> items = i.value()->getItemList();
		for (int j = 0; j < items.size(); ++j)
		{
			QDomElement m = doc.createElement("NodeItem");
			m.setAttribute("Type", QString::number(items.at(j)->getType()));
			m.setAttribute("Caption", items.at(j)->getCaption());
			l.appendChild(m);
		}

		xmlRoot.appendChild(l);
	}

	KSaveFile file(KStandardDirs::locateLocal("data", TYPE_FILE));
	if( !file.open(QIODevice::WriteOnly))
		return;
	QTextStream ts(&file);
	ts << doc.toString();
	file.close();
}

void XmlDataStore::loadCustomNodeTypeDefinitions()
{
	QDomDocument doc;
	QFile file(KStandardDirs::locateLocal("data", TYPE_FILE));
	if (!file.open(QIODevice::ReadOnly))
		return;
	doc.setContent(&file);
	file.close();

	QDomElement xmlRoot = doc.documentElement();
	if (xmlRoot.tagName() != "CustomNodeTypeDefinitions")
		return;
	//TODO: test if right version
	QDomNode n = xmlRoot.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (e.tagName() == "TypeDefinition")
		{
			CustomNodeTypeDefinition *def = new CustomNodeTypeDefinition(e.attribute("name", "noname"));
			QDomNode m = e.firstChild();
			while (!m.isNull())
			{
				QDomElement f = m.toElement();
				if (f.tagName() == "NodeItem")
				{
					CustomNodeItem *item = new CustomNodeItem(
						f.attribute("Caption", ""),
						(CustomNodeItem::Type)f.attribute("Type", "0").toInt()
					);
					def->addItem(item);
				}
				m = m.nextSibling();
			}
			customNodeTypeDefinitions[def->getName()] = def;
		}
		n = n.nextSibling();
	}
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
	KSaveFile file(KStandardDirs::locateLocal("data", DATA_FILE));
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

void XmlDataStore::writeToXmlFile(QString fileName, Node* root){
	QDomDocument doc;
	doc.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"));
	QDomElement xmlRoot = doc.createElement("silence");
	doc.appendChild(xmlRoot);

	if (root == Controller::create()->getDataStore()->getRootNode()){
		for (int i = 0; i < root->getChildCount(); ++i)
		{
			addXmlNode(root->getChild(i), xmlRoot, doc);
		}
	} else {
		addXmlNode(root, xmlRoot, doc);
	}
	
	// write to file
	KSaveFile file(fileName);
	if( !file.open(QIODevice::WriteOnly))
		return;
	QTextStream ts(&file);
	ts << doc.toString();
	file.close();
}

void XmlDataStore::readFromXmlFile(QString fileName, Node* root){
	QDomDocument doc;
	QFile file(fileName);
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
		if (e.tagName() == "node")
			xmlToNode(root, n, doc, Controller::create()->getDataStore());
		n = n.nextSibling();
	}
	QList<Node*> nodes = root->toNodeList();
	for (int i=0; i<nodes.size(); ++i){
		// update ids to ensure uniq ids
		nodes.at(i)->setId(new NodeId);
		Controller::create()->getDataStore()->saveNode(nodes.at(i));
	}

	// tell the treemodel to update the treeview
	Controller::create()->getTreeView()->getTreeModel()->insertRows(0, 0);
}




