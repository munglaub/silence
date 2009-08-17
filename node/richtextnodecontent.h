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
		QString getMimeType();

		void setText(QString text);
		QString getText() const;
	
	signals:
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;

};

#endif // RICHTEXTNODECONTENT_H
