#ifndef DATASTORE_H
#define DATASTORE_H

#include "node/node.h"

class DataStore
{
	public:
		DataStore();
		~DataStore();

		Node* getRoot();
	
	private:
		Node *root;
};

#endif // DATASTORE_H

