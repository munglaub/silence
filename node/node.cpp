#include "controller.h"
#include "node/node.h"
#include <QDateTime>
#include <QString>


Node::Node(Node *parent)
{
	this->caption = "";
	this->parent = parent;
	
	content = NULL;
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
// TODO: welches ist richtig/besser??
	if (parent)
		return parent->children.indexOf(const_cast<Node*>(this));
//		return parent->children.indexOf(this);
	
	return 0;
}

/*
void Node::addChild(Node *child)
{
	children.append(child);
}

bool Node::addChild(Node *child, int position)
{
	if (position < 0 || position > children.size())
		return false;
	children.insert(position, child);
	return true;
}
*/

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

Node* Node::getChild(int index) const
{
	return children.value(index);
}

int Node::getChildCount() const
{
	return children.count();
}

Node* Node::getParent() const
{
	return parent;
}

NodeId Node::getId() const
{
	return id;
}

void Node::setId(NodeId id)
{
	this->id = id;
}

QString Node::getCaption() const
{
	return caption;
}

bool Node::setCaption(QString caption)
{
	this->caption = caption;
	change();
	emit changed(this);
	return true;
}

int Node::columnCount() const
{
	// the treeview has only 1 column
	return 1;
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
	emit changed(this);
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

QStringList Node::getLabels() const
{
	return labels;
}

void Node::addLabel(QString label)
{
	labels.append(label);
	change();
	emit changed(this);
}

void Node::addLabels(QStringList labels)
{
	this->labels = this->labels + labels;
}

void Node::change()
{
	setModificationDate(QDateTime::currentDateTime());
	emit changed(this);
}

