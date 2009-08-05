#include "node/nodeid.h"
#include <QString>

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

int NodeId::highestid = 0;

void NodeId::init(int nodeid)
{
	id = nodeid;
	if (id > highestid)
		highestid = id;
}


QString* NodeId::toString()
{
	QString *result = new QString;
	result->setNum(id);
	return result;
}


