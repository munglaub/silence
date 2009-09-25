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
		virtual QWidget* getWidget() = 0;
		virtual QHash<QString, QString>* getMetaInfos() = 0;
		virtual void addMetaInfo(QString key, QString value) = 0;
		virtual QString getMimeType() = 0;
		virtual bool contains(const QString& value) = 0;

		virtual QDomElement getXmlData(QDomDocument &doc) = 0;
		virtual void setXmlData(QDomElement &xmlNode) = 0;
		virtual QPixmap getPixmap() = 0;
		virtual QIcon getIcon() = 0;
};

#endif // ABSTRACTNODECONTENT_H
