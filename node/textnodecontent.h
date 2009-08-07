#ifndef TEXTNODECONTENT_H
#define TEXTNODECONTENT_H

#include "node/abstractnodecontent.h"
#include "gui/textedit.h"

class TextNodeContent : public AbstractNodeContent
{
	public:
		TextNodeContent();
		~TextNodeContent();

		void setText(QString &text);
		QString getText() const;
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();

	private:
		TextEdit *widget;
		QHash<QString, QString> *metaInfos;
		QString text;
};

#endif // TEXTNODECONTENT_H


