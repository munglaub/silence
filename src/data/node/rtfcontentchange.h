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

#ifndef RTFCONTENTCHANGE_H
#define RTFCONTENTCHANGE_H

#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/richtextnodecontent.h"
#include "src/gui/view/richtextedit.h"

/*!\class RtfContentChange
 * \brief A class to store changes of the RichTextNodeContent.
 *
 * Use this class to store changes of the RichTextNodeContent for a NotificationBox.
 *
 * \author Manuel Unglaub
 */
class RtfContentChange : public AbstractContentChange
{
	public:
		/*! The constructor.
		 *
		 * Construct a RtfContentChange.
		 * \param change The changed content.
		 * \param content The unsaved RichTextNodeContent.
		 * \param edit The contentview to edit the content.
		 */
		RtfContentChange(QString change, RichTextNodeContent *content, RichTextEdit *edit);

		void updateContent();
		void updateContentView();
	private:
		QString change;
		RichTextNodeContent *content;
		RichTextEdit *edit;
};

#endif // RTFCONTENTCHANGE_H

