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

		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();
		QString getMimeType();
		void setSyntax(QString syntax);
	
	signals:
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
};

#endif // TEXTNODECONTENT_H


