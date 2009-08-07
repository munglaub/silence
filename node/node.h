#ifndef NODE_H
#define NODE_H

#include "node/abstractnodecontent.h"
#include "node/nodeid.h"
#include <QString>
#include <QStringList>

class Node
{
	public:
		// Konstruktoren & Destruktoren
		Node(QString caption, Node *parent = 0); 
		~Node();

		int getIndex() const;

		Node* getParent() const;

		// children
//		void addChild(Node *child);
//		bool addChild(Node *child, int position);
		bool addChildren(int position, int count);
		Node* getChild(int index) const;
		int getChildCount() const;
		bool removeChildren(int position, int count);
		

		// caption
		QString getCaption() const;
		bool setCaption(QString caption);
		
		// content
		AbstractNodeContent* getContent() const;
		void setContent(AbstractNodeContent *content);

		int columnCount() const;
		
	private:
		NodeId id;
		QString caption;
		AbstractNodeContent *content;
		// maybe some sort of an icon
/*
		NodeContent content;
		QStringList tags;
		QString mimeType;
		QDate creationDate;
		QDate modificationDate;
*/		
		Node *parent;
		QList<Node*> children;
};

#endif // NODE_H
