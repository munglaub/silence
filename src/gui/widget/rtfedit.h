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

#ifndef RTFEDIT_H
#define RTFEDIT_H

#include <QTextEdit>
#include <QList>
#include <QAction>


/*!\class RtfEdit
 * \brief A widget to edit RTF text.
 *
 * This widget is used by the RichTextEdit. It is an area to edit the RTF text.
 *
 * \author Manuel Unglaub
 */
class RtfEdit : public QTextEdit
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the RtfEdit which is a child of parent.
		 *
		 * \param parent The parent of this RtfEdit.
		 */
		RtfEdit(QWidget *parent = 0);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~RtfEdit();

		/*!
		 * Add actions to the context menu of this RtfEdit.
		 *
		 * \param actions The actions which will be added to the context menu.
		 */
		void addContextActions(QList<QAction*> actions);

		/*!
		 * This function returns true if the contents of the MIME data object, specified by source, can be decoded and inserted into the document.
		 *
		 * \param source The MIME data object.
		 * \return True if the contents of the MIME data object can be decoded and inserted into the document.
		 */
		bool canInsertFromMimeData(const QMimeData *source) const;

		/*!
		 * This function inserts the contents of the MIME data object, specified by source, into the RtfEdit at the current cursor position.
		 *
		 * \param source The MIME data object which will be inserted.
		 */
		void insertFromMimeData(const QMimeData *source);

	private:
		void contextMenuEvent(QContextMenuEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

		QList<QAction*> actions;

};

#endif // RTFEDIT_H


