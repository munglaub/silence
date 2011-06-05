/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include "src/data/node/abstractnodecontent.h"
#include "src/data/node/node.h"


/*!\class TextNodeContent
 * \brief A text content with syntax information for the Node.
 *
 * This content contains plain text with metainfos and a syntax information which is part of the metainfos.
 *
 * \author Manuel Unglaub
 */
class TextNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs a TextNodeContent.
		 */
		TextNodeContent();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~TextNodeContent();

		/*!
		 * Set the text of this TextNodeContent.
		 * \param text The text that will be assigned to this TextNodeContent.
		 * \sa getText()
		 */
		void setText(QString text);

		/*!
		 * Get the text of this TextNodeContent.
		 * \return The text of this TextNodeContent.
		 * \sa setText()
		 */
		QString getText() const;

		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);
		
		AbstractContentView* getWidget();
		QHash<QString, QString>* getMetaInfos();
		void addMetaInfo(QString key, QString value);
		QString getMimeType();
		bool contains(const QString& value);

		/*!
		 * Set the syntax of this TextNodeContent.
		 * \param syntax The syntax that will be assigned to this TextNodeContent.
		 * \sa TextEdit::setSyntax()
		 */
		void setSyntax(QString syntax);

		QPixmap getPixmap();
		QIcon getIcon();
		QString toString();
		void setParentNode(Node* parent);
		QString getHtml();
	
	signals:
		/*!
		 * This signal will be emitted after calling setText(), addMetaInfo() and setSyntax().
		 */
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
};

#endif // TEXTNODECONTENT_H


