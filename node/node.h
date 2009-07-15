#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		// Konstruktoren & Destruktoren
		Node(); 
		~Node();

		// getter & setter
		// ..

	private:
		NodeCaption caption;
		NodeContent content;
		QStringList metaInfos;
		QString mimeType;

};

#endif // NODE_H
