#ifndef NODECAPTION_H
#define NODECAPTION_H

class NodeCaption
{
	public:
		NodeCaption(const QString &caption);
		~NodeCaption();

		QString getCaption();
	
	private:
		QString caption;

};

#endif // NODECAPTION_H


