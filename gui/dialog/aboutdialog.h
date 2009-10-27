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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>


/*!\class AboutDialog
 * \brief Some infos about Silence.
 *
 * This dialog shows some informations about Silence.
 *
 * \author Manuel Unglaub
 */
class AboutDialog : public QDialog
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the AboutDialog which is a child of parent.
		 * \param parent The parent of this AboutDialog.
		 * \param f The dialog flags f are passed on to the QDialog constructor.
		 */
		AboutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~AboutDialog();

	private:
                QGridLayout *subLayout,
                            *layout;
                QLabel      *logo,
                            *version,
                            *authors;
		QPushButton *quit;
};

#endif // ABOUTDIALOG_H
