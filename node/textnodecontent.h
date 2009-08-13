#ifndef TEXTNODECONTENT_H
#define TEXTNODECONTENT_H

#include "node/abstractnodecontent.h"

class TextNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		TextNodeContent();
		~TextNodeContent();

		void setText(QString text);
		QString getText() const;
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();
		QString getMimeType();
	
	signals:
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
};

#endif // TEXTNODECONTENT_H


