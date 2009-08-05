#include "data/datastore.h"

DataStore::DataStore()
{
	root = new Node("root");
}

DataStore::~DataStore()
{
	delete root;
}

Node* DataStore::getRoot()
{
	return root;
}

