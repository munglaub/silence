#ifndef NODE_H
#define NODE_H

//#include "node/nodecaption.h"
#include "node/nodeid.h"
#include <QString>
#include <QStringList>

class Node
{
	public:
		// Konstruktoren & Destruktoren
		Node(QString caption, Node *parent = 0); 
		~Node();

		int getIndex();

		Node* getParent();

		// children
//		void addChild(Node *child);
//		bool addChild(Node *child, int position);
		bool addChildren(int position, int count);
		Node* getChild(int index);
		int getChildCount() const;
		// TODO: ueberdenken..
		bool removeChildren(int position, int count);
		

		// caption
		QString getCaption();
		bool setCaption(QString caption);

		int columnCount() const;
		
		

	private:
		NodeId id;
		QString caption;
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
