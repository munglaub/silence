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

#ifndef ABSTRACTNODECONTENT_H
#define ABSTRACTNODECONTENT_H

#include <QDomDocument>
#include <QHash>
#include <QIcon>
#include <QWidget>
#include "src/gui/view/abstractcontentview.h"


/*!\class AbstractNodeContent
 * \brief An abstract base for the Node contents.
 *
 * This abstract class provides an interface for the contents of the Node.
 *
 * \author Manuel Unglaub
 */
class AbstractNodeContent : public QObject
{
	public:
		/*!
		 * Get a widget to view and modify this content. The content will configure the widget properly for its needs and fill it with the necessary data.
		 * \return A widget to view and modify this content.
		 */
		virtual AbstractContentView* getWidget() = 0;

		/*!
		 * Get the metainfos of this content. The metainfos are key value pairs.
		 * \return The metainfos of this content.
		 */
		virtual QHash<QString, QString>* getMetaInfos() = 0;

		/*!
		 * Add a meta info to this content.
		 * \param key The key of the meta info.
		 * \param value The value of the meta info.
		 */
		virtual void addMetaInfo(QString key, QString value) = 0;

		/*!
		 * Get the mimetype of this content.
		 * \return The mimetype of this content.
		 */
		virtual QString getMimeType() = 0;

		/*!
		 * Find out if the content contains a specific string.
		 * \param value The QString to look for in this content.
		 * \return True if the content contains the string.
		 */
		virtual bool contains(const QString& value) = 0;

		/*!
		 * Creates a QDomElemet which contains the data of this content. Only the main part of the data, not the metainfos.
		 * \param doc The QDomDocument to create the xml elements.
		 * \return The QDomElement which contains the data of this content.
		 * \sa setXmlData()
		 */
		virtual QDomElement getXmlData(QDomDocument &doc) = 0;

		/*!
		 * Initialize this content with the data provided by the QDomElement.
		 * \param xmlNode The QDomElement containing the data for this content.
		 * \sa getXmlData()
		 */
		virtual void setXmlData(QDomElement &xmlNode) = 0;

		/*!
		 * Get an icon as a QPixmap to indicate the type of the content. The Pixmap should be the size of 16x16 pixel. It should also be similar to the icon provided by the getIcon() function.
		 * \return A pixmap which indicates the type of the content.
		 * \sa getIcon()
		 */
		virtual QPixmap getPixmap() = 0;

		/*!
		 * Get an icon as a QIcon to indicate the type of the content. The icon should be the size of 64x64 pixel. It should also be similar to the icon provided by the get Pixmap() function.
		 * \return A icon which indicates the type of the content.
		 * \sa getPixmap()
		 */
		virtual QIcon getIcon() = 0;

		/*!
		 * Transform the content to a QString. This string should only contain plain text information.
		 *
		 * \return The content as a QString.
		 */
		virtual QString toString() = 0;
};

#endif // ABSTRACTNODECONTENT_H


