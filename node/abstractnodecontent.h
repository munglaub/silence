#ifndef ABSTRACTNODECONTENT_H
#define ABSTRACTNODECONTENT_H

#include <QWidget>
#include <QHash>

class AbstractNodeContent
{
	public:
		virtual QWidget* getWidget() { return NULL; };
		virtual QHash<QString, QString>* getMetaInfos() { return NULL; };

		// mimeType ?!

		//virtual foo getData(); // gibt ein datenpaket zum speichern des contents zurueck
};

#endif // ABSTRACTNODECONTENT_H
