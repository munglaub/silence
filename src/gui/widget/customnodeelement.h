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

#ifndef CUSTOMNODEELEMENT_H
#define CUSTOMNODEELEMENT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "src/data/node/customnodeitem.h"
#include "src/gui/widget/customdatawidget.h"


/*!\class CustomNodeElement
 * \brief A widget for a CustomNodeItem.
 *
 * This class provides a widget to display and modify a CustomNodeItem. It uses a CustomDataWidget to show the data of the item.
 *
 * \author Manuel Unglaub
 */
class CustomNodeElement : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the CustomNodeElement.
		 * \param item The item which will be displayed.
		 * \param showModifiers If true a remove button will be shown.
		 * \param parent The parent of this widget.
		 */
		CustomNodeElement(CustomNodeItem *item, bool showModifiers = false, QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~CustomNodeElement();

		/*!
		 * Set data to the CustomDataWidget.
		 * \param data This data will be set to the CustomDataWidget.
		 */
		void setData(QString data);

		/*!
		 * Get the data from the CustomDataWidget.
		 * \return The data from the CustomDataWidget.
		 */
		QString getData() const;

	signals:
		/*!
		 * This signal will be emitted when the remove button is clicked.
		 * \param element A pointer to this CustomNodeItem.
		 * \param item A pointer to the CustomNodeItem contained in this CustomNodeElement.
		 */
		void remove(CustomNodeElement *element, CustomNodeItem *item);

		/*!
		 * This signal will be emitted when the content of this widget changes.
		 */
		void changed();

	public slots:
		/*!
		 * The data from the widget will be written into the CustomNodeItem.
		 */
		void save();

	private slots:
		void onRemove();
		void onChange();

	private:
		QHBoxLayout *layout;
		QLabel *caption;
		CustomDataWidget *datawidget;
		QPushButton *btnRemove;

		CustomNodeItem *item;
};

#endif // CUSTOMNODEELEMENT_H

