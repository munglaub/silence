#ifndef NODE_H
#define NODE_H

#include "node/nodecaption.h"
#include "node/nodeid.h"
#include <QString>
#include <QStringList>

class Node
{
	public:
		// Konstruktoren & Destruktoren
		Node(); 
		~Node();

		// getter & setter
		// ..

	private:
		NodeId id;
		// maybe some sort of an icon
		NodeCaption caption;
		NodeContent content;
		QStringList tags;
		QString mimeType;
		QDate creationDate;
		QDate modificationDate;
		
		Node *parent;
		QList<Node> children;
};

#endif // NODE_H
