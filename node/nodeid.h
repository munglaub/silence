#ifndef NODEID_H
#define NODEID_H

#include <QString>

class NodeId
{
	public:
		NodeId();
		NodeId(int nodeid);
		~NodeId();

		QString* toString();

	private:
		void init(int nodeid);
		static int highestid;
		int id;
};

#endif // NODEID_H


