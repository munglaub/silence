#ifndef ABSTRACTNODECONTENT_H
#define ABSTRACTNODECONTENT_H

#include <QWidget>
#include <QHash>
#include <QDomDocument>
#include <QIcon>

class AbstractNodeContent : public QObject
{
	public:
		virtual QWidget* getWidget() { return NULL; };
		virtual QHash<QString, QString>* getMetaInfos() { return NULL; };
		virtual void addMetaInfo(QString key, QString value) { key = value; };
		virtual QString getMimeType() { return ""; };

		virtual QDomElement getXmlData(QDomDocument &doc) { return doc.createElement(""); };
		virtual void setXmlData(QDomElement &xmlNode) { xmlNode.firstChild(); };
		virtual QPixmap getPixmap() { return NULL; };
		virtual QIcon getIcon() { return QIcon(); };
};

#endif // ABSTRACTNODECONTENT_H
