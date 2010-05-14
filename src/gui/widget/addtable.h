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

#ifndef ADDTABLE_H
#define ADDTABLE_H

#include <knuminput.h>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>


/*!\class AddTable
 * \brief A wiedget to add tables.
 *
 * This widget provides a gui to create a table and get an HTML table tag with a specified number of columns and rows.
 *
 * \author Manuel Unglaub
 */
class AddTable : public QGridLayout
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the AddTable which is a child of parent.
		 *
		 * \param parent The parent of this AddTable.
		 */
		AddTable(QWidget *parent);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~AddTable();

	public slots:
		/*!
		 * Connect to this slot to destroy this object.
		 */
		void exit();

	signals:
		/*!
		 * This signal is emited when the user clicked the ok button.
		 *
		 * \param html Containing the HTML table tag that represents the table with the specified number of columns and rows.
		 */
		void addedTable(const QString &html);

	private slots:
		void addTable();

	private:
		KIntSpinBox *sbColumns,
					*sbRows;
		QLabel	*lblColumns,
				*lblRows;
		QPushButton *btnOk,
					*btnCancel;
};

#endif // ADDTABLE_H

