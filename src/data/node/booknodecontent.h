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


#include <KIcon>
#include "src/data/node/abstractnodecontent.h"
#include "src/data/node/node.h"


/*!\class BookNodeContent
 * \brief A content type which shows the content of its subnodes.
 *
 * The BookNodeContent doesn't have a content of its own except the usual metainfos. It will however
 * show the contents of the subnodes of its node as a html page. It will generate a table of contents
 * and create links to make the navigation easier.
 *
 * \author Manuel Unglaub
 */
class BookNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the BookNodeContent.
		 */
		BookNodeContent();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
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
		QString visitNodesForContent(QString html, Node *node, QString &backlink);
};

#endif // BOOKNODECONTENT_H

