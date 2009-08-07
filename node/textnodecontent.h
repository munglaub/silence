#ifndef TEXTNODECONTENT_H
#define TEXTNODECONTENT_H

#include "node/abstractnodecontent.h"

class TextNodeContent : AbstractNodeContent
{
	public:
		TextNodeContent();
		~TextNodeContent();
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();

	private:
		QWidget* widget;
		QHash<QString, QString>* metaInfos;
};

#endif // TEXTNODECONTENT_H


