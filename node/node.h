#ifndef NODE_H
#define NODE_H

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
		NodeCaption caption;
		NodeContent content;
		QStringList metaInfos;
		QString mimeType;
		QDate creationDate;
		QDate modificationDate;
		
		Node *parent;
		QList<Node> children;
};

#endif // NODE_H
