#ifndef TEXTNODECONTENT_H
#define TEXTNODECONTENT_H

#include "node/abstractnodecontent.h"

class TextNodeContent : public AbstractNodeContent
{
	public:
		TextNodeContent();
		~TextNodeContent();

		void setText(QString text);
		QString getText() const;
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();
		QString getMimeType();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
};

#endif // TEXTNODECONTENT_H


