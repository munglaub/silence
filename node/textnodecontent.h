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

#ifndef TEXTNODECONTENT_H
#define TEXTNODECONTENT_H

#include "node/abstractnodecontent.h"

class TextNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		TextNodeContent();
		~TextNodeContent();

		void setText(QString text);
		QString getText() const;

		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);
		
		QWidget* getWidget();
		QHash<QString, QString>* getMetaInfos();
		void addMetaInfo(QString key, QString value);
		QString getMimeType();
		void setSyntax(QString syntax);

		QPixmap getPixmap();
		QIcon getIcon();
	
	signals:
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;

		QIcon icon;
		QPixmap pixmap;

		void setGraphics();
};

#endif // TEXTNODECONTENT_H


