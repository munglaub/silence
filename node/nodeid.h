#ifndef NODEID_H
#define NODEID_H

#include <QString>

class NodeId
{
	public:
		NodeId();
		NodeId(int id);
		~NodeId();

		QString toString();

	private:
		static int highestid = 0;
		int id;
};

#endif // NODEID_H


