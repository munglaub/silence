#ifndef ABSTRACTNODECONTENT_H
#define ABSTRACTNODECONTENT_H

#include <QWidget>
#include <QHash>

class AbstractNodeContent : public QObject
{
	public:
		virtual QWidget* getWidget() { return NULL; };
		virtual QHash<QString, QString>* getMetaInfos() { return NULL; };
		virtual QString getMimeType() { return ""; };

		//virtual foo getData(); // gibt ein datenpaket zum speichern des contents zurueck
};

#endif // ABSTRACTNODECONTENT_H
