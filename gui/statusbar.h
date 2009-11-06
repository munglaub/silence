/*
 * Silence
 *
 * Copyright (C) 2009 Manuel Unglaub
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

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>


/*!\class StatusBar
 * \brief The statusbar for the MainWindow.
 *
 * This StatusBar is used in the MainWindow to show some status informations.
 *
 * \author Manuel Unglaub
 */
class StatusBar : public QStatusBar
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the StatusBar which is a child of parent.
		 * \param parent The parent of this StatusBar.
		 */
		StatusBar(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~StatusBar();

		/*!
		 * Display the currently selected nodes name.
		 * \param name The string which will be shown in this StatusBar.
		 */
		void setNodeName(QString name);
	
	public slots:
		/*!
		 * Display the current cursor position in this StatusBar.
		 * \param line Set the line of the current cursor position.
		 * \param col Set the column of the current cursor position.
		 */
		void setCursorPosition(int line, int col);

		/*!
		 * Show if the currently selected node is saved.
		 * \param saved If true it will show that the content is saved and if it is false it will show that the content is changend.
		 */
		void setSaveStatus(bool saved);

	private:
		QLabel	*nodeName,
				*saveStatus,
				*cursorPos;
};

#endif // STATUSBAR_H



