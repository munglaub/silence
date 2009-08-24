#include "data/datastore.h"

DataStore::DataStore()
{
	root = new Node();
}

DataStore::~DataStore()
{
	delete root;
}

Node* DataStore::getRoot()
{
	return root;
}

