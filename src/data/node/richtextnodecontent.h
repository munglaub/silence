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

#ifndef RICHTEXTNODECONTENT_H
#define RICHTEXTNODECONTENT_H

#include "src/data/node/abstractnodecontent.h"


/*!\class RichTextNodeContent
 * \brief A content with formatted text for the Node.
 *
 * This content contains formatted text with meta infos.
 *
 * \author Manuel Unglaub
 */
class RichTextNodeContent : public AbstractNodeContent
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs a RichTextNodeContent.
		 */
		RichTextNodeContent();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~RichTextNodeContent();
		
		AbstractContentView* getWidget();
		QHash<QString, QString>* getMetaInfos();
		void addMetaInfo(QString key, QString value);
		QString getMimeType();
		bool contains(const QString& value);

		/*!
		 * Set the text of this RichTextNodeContent.
		 * \param text The text that will be assigned to this RichTextNodeContent.
		 * \sa getText()
		 */
		void setText(QString text);

		/*!
		 * Get the text of this RichTextNodeContent.
		 * \return The text of this RichTextNodeContent.
		 * \sa setText()
		 */
		QString getText() const;

		QDomElement getXmlData(QDomDocument &doc);
		void setXmlData(QDomElement &xmlNode);

		QPixmap getPixmap();
		QIcon getIcon();

		QString toString();
	
	signals:
		/*!
		 * This signal will be emitted after calling addMetaInfo() and setText().
		 */
		void changed();

	private:
		QHash<QString, QString> *metaInfos;
		QString text;
		QIcon icon;

};

#endif // RICHTEXTNODECONTENT_H


