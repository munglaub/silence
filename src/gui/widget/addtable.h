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


class AddTable : public QGridLayout
{
	Q_OBJECT

	public:
		AddTable(QWidget *parent);
		~AddTable();

	public slots:
		void exit();

	signals:
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

