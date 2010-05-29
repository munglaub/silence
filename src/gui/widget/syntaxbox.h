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

#ifndef SYNTAXBOX_H
#define SYNTAXBOX_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>


/*!\class SyntaxBox
 * \brief A widget to select a syntax.
 *
 * This widget provides a combobox with the available syntax options and an optional describing label.
 *
 * \author Manuel Unglaub
 */
class SyntaxBox : public QWidget
{
	public:
		/*! The constructor.
		 *
		 * Constructs the SyntaxBox which is a child of parent.
		 * \param showLabel Indicates if the describing label will be shown.
		 * \param parent The parent of this SyntaxBox.
		 */
		SyntaxBox(bool showLabel = true, QWidget *parent = 0);

		/*! The destructro.
		 *
		 * Destroys the object.
		 */
		~SyntaxBox();

		/*!
		 * Get the selected syntax.
		 * \return A QString with the selected syntax.
		 */
		QString getSyntax();

		/*!
		 * Select a specific syntax.
		 * \param syntax The syntax which will be selected.
		 */
		void setSyntax(QString syntax);
	
	private:
		QHBoxLayout *layout;
		QLabel *lblSyntax;
		QComboBox *synbox;
};

#endif // SYNTAXBOX_H
