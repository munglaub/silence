/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#ifndef CUSTOMNODECONTENT_H
#define CUSTOMNODECONTENT_H

#include "src/data/node/abstractnodecontent.h"
#include "src/data/node/customnodetypedefinition.h"


class CustomNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		CustomNodeContent(CustomNodeTypeDefinition *typeDefinition);
		CustomNodeContent(QString mimetype);
		~CustomNodeContent();

		AbstractContentView* getWidget();
		QHash<QString, QString>* getMetaInfos();
		void addMetaInfo(QString key, QString value);
		QString getMimeType();
		bool contains(const QString& value);
		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);
		QPixmap getPixmap();
		QIcon getIcon();
		QString toString();

	signals:
		void changed();
	
	private slots:
		void onChange();

	private:
		QHash<QString, QString> *metaInfos;
		QList<CustomNodeItem*> items;
		QString mimetype;

		void init(QString mimetype);
		void readXmlContentItems(QDomElement &xmlNode);
};

#endif // CUSTOMNODECONTENT_H

