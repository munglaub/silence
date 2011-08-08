/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QTextBrowser>
#include <QVBoxLayout>
#include "src/gui/view/abstractcontentview.h"


/*!\class BookView
 * \brief View to show a BookNodeContent or any HTML content.
 *
 * This BookView should be used to show HTML content (mainly the BookNodeContent). It only
 * shows the content and can not edit it.
 * This BookView can handel Silence links as well as links to external content.
 *
 * \author Manuel Unglaub
 */
class BookView : public AbstractContentView
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the BookView.
		 */
		BookView();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~BookView();

		bool hasChanged();
		AbstractContentChange* getChange();

		/*!
		 * Set the html content which will be shown.
		 * \param html The html content to show.
		 */
		void setHtmlContent(QString html);

	private slots:
		void onClick(const QUrl& url);

	private:
		QVBoxLayout *layout;
		QTextBrowser *view;

};

#endif // BOOKVIEW_H

