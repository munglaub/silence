#include "node/nodeid.h"
#include <QString>

int NodeId::highestid = 0;

NodeId::NodeId()
{
	init(highestid + 1);
}

NodeId::NodeId(int nodeid)
{
	init(nodeid);
}

NodeId::~NodeId()
{
}

void NodeId::init(int nodeid)
{
	id = nodeid;
	if (id > highestid)
		highestid = id;
}

int NodeId::getId() const
{
	return id;
}

QString* NodeId::toString()
{
	QString *result = new QString;
	result->setNum(id);
	return result;
}


