#include "node/node.h"

Node::Node(QString caption, Node *parent)
{
	this->caption = caption;
	this->parent = parent;
}

Node::~Node()
{
	qDeleteAll(children);
}

int Node::getIndex()
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
		Node *item = new Node("", this);
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

Node* Node::getChild(int index)
{
	return children.value(index);
}

int Node::getChildCount() const
{
	return children.count();
}

Node* Node::getParent()
{
	return parent;
}

QString Node::getCaption()
{
	return caption;
}

bool Node::setCaption(QString caption)
{
	this->caption = caption;
	return true;
}

int Node::columnCount() const
{
	// the treeview has only 1 column
	return 1;
}

