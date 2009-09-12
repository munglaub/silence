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
		bool contains(const QString& value);

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


