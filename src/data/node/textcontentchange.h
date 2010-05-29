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

#ifndef TEXTCONTENTCHANGE_H
#define TEXTCONTENTCHANGE_H

#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/textnodecontent.h"
#include "src/gui/view/textedit.h"


/*!\class TextContentChange
 * \brief A class to store changes of the TextNodeContent.
 *
 * Use this class to store changes of the TextNodeContent for a NotificationBox.
 *
 * \author Manuel Unglaub
 */
class TextContentChange : public AbstractContentChange
{
	public:
		/*! The constructor.
		 *
		 * Construct a TextContentChange.
		 * \param change The changed content.
		 * \param content The unsaved TextNodeContent.
		 * \param edit The contentview to edit the content.
		 */
		TextContentChange(QString change, TextNodeContent *content, TextEdit *edit);

		void updateContent();
		void updateContentView();
	private:
		QString change;
		TextNodeContent *content;
		TextEdit *edit;
};

#endif // TEXTCONTENTCHANGE_H

