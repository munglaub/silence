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

#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QGridLayout>
#include <QGroupBox>
#include <klineedit.h>
#include <QPushButton>


/*!\class InputWidget
 * \brief A input widget.
 *
 * This widget consists of a title, a lineedit, a OK button and a cancel button. Use it for simple inputs.
 *
 * \author Manuel Unglaub
 */
class InputWidget : public QGroupBox
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the InputWidget which is a child of parent.
		 * \param parent The parent of this InputWidget.
		 */
		InputWidget(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~InputWidget();

		/*!
		 * Get the users input.
		 *
		 * \return The input in the lineedit.
		 */
		QString getInput();

	public slots:
		/*!
		 * Show the InputWidget, clear the lineedit, set the title and set the focus to the lineedit.
		 *
		 * \param title The title of this InputWidget.
		 */
		void show(QString title);

	signals:
		/*!
		 * The ok button was clicked or the user hit enter in the lineedit.
		 */
		void done();

	private slots:
		void confirm();
		void updateButtons();

	private:
		QGridLayout *layout;
		KLineEdit *inputEdit;
		QPushButton *okBtn,
					*cancelBtn;
};


#endif // INPUTWIDGET_H


