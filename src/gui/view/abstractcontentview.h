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

#ifndef ABSTRACTCONTENTVIEW_H
#define ABSTRACTCONTENTVIEW_H

#include <QLayout>
#include <QWidget>
#include "src/data/node/abstractcontentchange.h"


/*!\class AbstractContentView
 * \brief An interface for widgets to display and edit the content of the nodes.
 *
 * Inherit from this class to create a class to edit and display the content of nodes.
 *
 * \author Manuel Unglaub
 */
class AbstractContentView : public QWidget
{
	public:
		/*!
		 * Find out if any change was made.
		 *
		 * \return True if the content was changed.
		 */
		virtual bool hasChanged() = 0;

		/*!
		 * Get the change made to the content.
		 *
		 * \return The change made to the content.
		 */
		virtual AbstractContentChange* getChange() = 0;
};

#endif // ABSTRACTCONTENTVIEW_H

