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

#ifndef CUSTOMCONTENTCHANGE_H
#define CUSTOMCONTENTCHANGE_H

#include <QList>
#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/customnodeitem.h"
#include "src/gui/view/customcontentview.h"


/*!\class CustomContentChange
 * \brief A class to store changes of a CustomNodeContent
 *
 * Use this class to store changes of the TextNodeContent for a NotificationBox.
 *
 * \author Manuel Unglaub
 */
class CustomContentChange : public AbstractContentChange
{
	public:
		/*! The constructor.
		 *
		 * Constructs the CustomContentChange.
		 * \param items The involved CustomNodeItems.
		 * \param data The changed content.
		 * \param view The contentview to edit the content.
		 */
		CustomContentChange(QList<CustomNodeItem*> items, QStringList data, CustomContentView *view);

		void updateContent();
		void updateContentView();

	private:
		CustomContentView *view;
		QList<CustomNodeItem*> items;
		QStringList data;
};

#endif // CUSTOMCONTENTCHANGE_H

