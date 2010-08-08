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

#ifndef CUSTOMNODEITEM_H
#define CUSTOMNODEITEM_H

#include <QString>
#include <QObject>

/*!\class CustomNodeItem
 * \brief An item of the CustomNodeContent.
 *
 * A CustomNodeContent contains a number of CustomNodeItems.
 * The CustomNodeItem has a type, a caption and data.
 *
 * \author Manuel Unglaub
 */
class CustomNodeItem : public QObject
{
	Q_OBJECT

	public:
		/*!
		 * This type describes the data of this CustomNodeItem and determines how to interpret it.
		 */
		enum Type {
			String,		/*!< A simple string. */
			Text,		/*!< A longer text. */
			Integer,	/*!< A integer. */
			Number,		/*!< A number (double). */
			Boolean,	/*!< A boolean (true or false) */
			Image		/*!< An image. */
		};

		/*! The constructor.
		 *
		 * Constructs the CustomNodeItem with a caption and a type.
		 * \param caption The caption of this CustomNodeItem.
		 * \param type The type of this CustomNodeItem.
		 */
		CustomNodeItem(QString caption, CustomNodeItem::Type type);

		/*!
		 * Get the caption of this CustomNodeItem.
		 * \return The caption of this item.
		 */
		QString getCaption() const;

		/*!
		 * Get the type of this CustomNodeItem.
		 * \return The type of this item.
		 */
		Type getType() const;

		/*!
		 * Set the data of this CustomNodeItem.
		 * \param data The data assigned to this item.
		 */
		void setData(QString data);

		/*!
		 * Get the data of this CustomNodeItem.
		 * \return The data of this CustomNodeItem.
		 */
		QString getData() const;

	signals:
		/*!
		 * This signal will be emitted after the data of this CustomNodeItem changes.
		 */
		void changed();

	private:
		Type type;
		QString caption;
		QString data;
};

#endif // CUSTOMNODEITEM_H

