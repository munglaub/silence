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

#ifndef CUSTOMCONTENTVIEW_H
#define CUSTOMCONTENTVIEW_H

#include <QList>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "src/data/node/customnodeitem.h"
#include "src/gui/view/abstractcontentview.h"
#include "src/gui/widget/customnodeelement.h"


/*!\class CustomContentView
 * \brief A view for a CustomNodeContent
 *
 * This CustomContentView can show and modify a CustomNodeContent. Set its data with the setItems() function.
 * Each item will be displayed with help of the CustomNodeElement.
 *
 * \author Manuel Unglaub
 */
class CustomContentView : public AbstractContentView
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the CustomContentView.
		 */
		CustomContentView();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~CustomContentView();

		/*!
		 * Provide this CustomContentView with data.
		 * \param items The CustomNodeItems which will be shown and can be modified.
		 */
		void setItems(QList<CustomNodeItem*> items);

		bool hasChanged();
		AbstractContentChange* getChange();

		/*!
		 * Set data to the CustomNodeElements in this CustomContentView.
		 * \param data The data which will be set to the CustomNodeElements.
		 */
		void setData(QStringList data);

	private slots:
		void save();
		void contentChanged();

	private:
		QList<CustomNodeElement*> elements;
		QList<CustomNodeItem*> items;
		QVBoxLayout *layout;
		QScrollArea *scrollarea;
		QVBoxLayout *scrolllayout;
		QPushButton *btnSave;

		bool isChanged;

		void deleteElements();

};

#endif // CUSTOMCONTENTVIEW_H

