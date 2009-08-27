#ifndef DATASTORE_H
#define DATASTORE_H

#include "node/node.h"
#include <QObject>
#include <QDomDocument>


class DataStore : public QObject
{
	Q_OBJECT

	public:
		DataStore();
		~DataStore();

		Node* getRoot();

		void remove(Node *node);
		void add(Node *node);

	public slots:
		void save(Node *node);
	
	private:
		Node *root;

		void addXmlNode(Node* node, QDomElement &parent, QDomDocument &doc);
		void xmlToNode(Node* parentNode, QDomNode &xmlNode, QDomDocument &doc);
};

#endif // DATASTORE_H

