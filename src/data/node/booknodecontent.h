/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOOKNODECONTENT_H
#define BOOKNODECONTENT_H


#include "src/data/node/abstractnodecontent.h"
#include <KIcon>
#include "src/data/node/node.h"


//TODO: docu
class BookNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		BookNodeContent();
		~BookNodeContent();

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
		void setParentNode(Node* parent);
		QString getHtml();

	signals:
		/*!
		 * This signal will be emitted after calling addMetaInfo().
		 */
		void changed();
	
	private:
		Node *node;
		QHash<QString, QString> *metaInfos;

		QString createContent();
		QString visitNodesForCaption(QString html, Node *node);
		QString visitNodesForContent(QString html, Node *node);
};

#endif // BOOKNODECONTENT_H

