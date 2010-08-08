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

#ifndef CUSTOMDATAWIDGET_H
#define CUSTOMDATAWIDGET_H

#include <QWidget>


/*!\class CustomDataWidget
 * \brief An abstract class to display the data of a CustomNodeItem
 *
 * Inherit from this class to create a class to display and edit the data of a specific type of a CustomNodeItem.
 *
 * \author Manuel Unglaub
 */
class CustomDataWidget : public QWidget
{
	public:
		/*!
		 * Write the data from the widget into the CustomNodeItem.
		 */
		virtual void save() = 0;

		/*!
		 * Set data to this widget.
		 * \param data Set this data to this widget.
		 */
		virtual void setData(QString data) = 0;

		/*!
		 * Get the data of this widget.
		 * \return The data of this widget.
		 */
		virtual QString getData() const = 0;
};

#endif // CUSTOMDATAWIDGET_H

