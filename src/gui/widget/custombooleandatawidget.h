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

#ifndef CUSTOMBOOLEANDATAWIDGET_H
#define CUSTOMBOOLEANDATAWIDGET_H

#include <QCheckBox>
#include <QVBoxLayout>
#include "src/data/node/customnodeitem.h"
#include "src/gui/widget/customdatawidget.h"


/*!\class CustomBooleanDataWidget
 * \brief A widget for a CustomNodeItem with boolean data
 *
 * A checkbox to represent a boolean.
 *
 * \author Manuel Unglaub
 */
class CustomBooleanDataWidget : public CustomDataWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the CustomBooleanDataWidget.
		 * \param item The data of this CustomNodeItem will be displayed.
		 */
		CustomBooleanDataWidget(CustomNodeItem *item);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~CustomBooleanDataWidget();

		void save();
		void setData(QString data);
		QString getData() const;

	signals:
		/*!
		 * This signal will be emitted when the data changes.
		 */
		void changed();

	private slots:
		void onChange();

	private:
		CustomNodeItem *item;
		QVBoxLayout *layout;
		QCheckBox *checkbox;
};

#endif // CUSTOMBOOLEANDATAWIDGET_H

