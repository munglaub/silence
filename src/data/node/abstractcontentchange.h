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

#ifndef ABSTRACTCONTENTCHANGE_H
#define ABSTRACTCONTENTCHANGE_H

#include <QObject>

/*!\class AbstractContentChange
 * \brief An abstract base for changes in the contents of the nodes.
 *
 * This abstract class provides an interface for the different contents to store unsaved changed.
 *
 * \author Manuel Unglaub
 */
class AbstractContentChange : public QObject
{
	public:
		/*!
		 * Write the changes to the content.
		 */
		virtual void updateContent() = 0;

		/*!
		 * Write the changes into the specified contentview.
		 */
		virtual void updateContentView() = 0;
};

#endif // ABSTRACTCONTENTCHANGE_H

