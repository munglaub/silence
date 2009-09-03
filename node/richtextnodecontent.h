#ifndef RICHTEXTNODECONTENT_H
#define RICHTEXTNODECONTENT_H

#include "node/abstractnodecontent.h"
#include <QHash>
#include <QWidget>

class RichTextNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		RichTextNodeContent();
		~RichTextNodeContent();
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();
		void addMetaInfo(QString key, QString value);
		QString getMimeType();

		void setText(QString text);
		QString getText() const;

		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);

		QPixmap getPixmap();
		QIcon getIcon();
	
	signals:
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
		QIcon icon;
		QPixmap pixmap;

};

#endif // RICHTEXTNODECONTENT_H
