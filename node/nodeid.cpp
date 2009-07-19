#include "node/nodeid.h"
#include <QString>

NodeId::NodeId()
{
	this(highestid + 1);
}

NodeId::NodeId(int id)
{
	this.id = id;
	if (id > highestid)
		highestid = id;
}
NodeId::~NodeId()
{
}

QString NodeId::toString()
{
	QString *result = new QString;
	result->setNum(id);
	return result;
}


