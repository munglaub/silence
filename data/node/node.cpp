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

#include "controller.h"
#include "data/node/node.h"


Node::Node(Node *parent)
{
	this->caption = "";
	this->parent = parent;
	
	content = 0;
	creationDate = QDateTime::currentDateTime();
	modificationDate = QDateTime::currentDateTime();
}

Node::~Node()
{
	qDeleteAll(children);
	delete content;
}

int Node::getIndex() const
{
// TODO: whats the better way?
	if (parent)
		return parent->children.indexOf(const_cast<Node*>(this));
//		return parent->children.indexOf(this);
	
	return 0;
}

bool Node::addChildren(int position, int count)
{
	if (position < 0 || position > children.size())
		return false;

	for (int row = 0; row < count; ++row){
		Node *item = new Node(this);
		children.insert(position, item);
	}
	return true;
}

bool Node::removeChildren(int position, int count)
{
	if (position < 0 || position + count > children.size())
		return false;

	for (int row = 0; row < count; ++row){
		Node *item =  children.takeAt(position);
		delete item;
	}

	return true;
}

Node* Node::takeChild(int position)
{
	if (position >= 0 && position < children.size())
		return children.takeAt(position);
	else
		return 0;
}

bool Node::addChild(Node* child, int position)
{
	if (position < 0 || position > children.size())
		return false;
	children.insert(position, child);
	child->setParent(this);
	return true;
}

Node* Node::getChild(int index) const
{
	if (index < 0 || index >= children.size())
		return 0;
	return children.at(index);
}

int Node::getChildCount() const
{
	return children.count();
}

Node* Node::getParent() const
{
	return parent;
}

QList<Node*> Node::toNodeList()
{
	QList<Node*> result;
	result << this;
	for (int i = 0; i < children.size(); ++i)
		result << children.at(i)->toNodeList();
	return result;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

NodeId Node::getId() const
{
	return id;
}

void Node::setId(NodeId id)
{
	this->id = id;
}

bool Node::contains(Node* node)
{
	if (children.contains(node))
		return true;
	else {
		bool result = false;
		for (int i = 0; i < children.size() && !result; ++i)
			result = children.at(i)->contains(node);
		return result;
	}
}

QString Node::getCaption() const
{
	return caption;
}

bool Node::setCaption(QString caption)
{
	this->caption = caption;
	change();
	return true;
}

AbstractNodeContent* Node::getContent() const
{
	return content;
}

void Node::setContent(AbstractNodeContent *content)
{
	this->content = content;
	connect(content, SIGNAL(changed()), this, SLOT(change()));
	change();
}

QDateTime Node::getCreationDate() const
{
	return creationDate;
}

void Node::setCreationDate(QDateTime date)
{
	creationDate = date;
}

QDateTime Node::getModificationDate() const
{
	return modificationDate;
}

void Node::setModificationDate(QDateTime date)
{
	modificationDate = date;
}

QStringList* Node::getLabels()
{
	return &labels;
}

void Node::addLabel(QString label)
{
	labels.append(label);
	change();
}

void Node::addLabels(QStringList labels)
{
	this->labels = this->labels + labels;
	change();
}

bool Node::removeLabel(QString label)
{
	bool result = labels.removeOne(label);
	if (result)
		change();
	return result;
}

void Node::change()
{
	setModificationDate(QDateTime::currentDateTime());
	emit changed(this);
}

