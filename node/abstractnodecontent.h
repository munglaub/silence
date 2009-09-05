/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
 *
 * This file is part of Silence.
 *
 * Silence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version GPLv2 only of the License.
 *
 * Silence is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

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
