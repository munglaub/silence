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

#include <klocalizedstring.h>
#include "src/gui/widget/addtable.h"


AddTable::AddTable(QWidget *parent)
{
	setAlignment(Qt::AlignLeft);
	int row = 0;

	lblRows = new QLabel(i18n("Rows"));
	addWidget(lblRows, row, 0);
	sbRows = new KIntSpinBox(1, 100, 1, 3, parent);
	sbRows->setMinimumWidth(100);
	addWidget(sbRows, row, 1);
	++row;

	lblColumns = new QLabel(i18n("Columns"));
	addWidget(lblColumns, row, 0);
	sbColumns = new KIntSpinBox(1, 100, 1, 3, parent);
	sbColumns->setMinimumWidth(100);
	addWidget(sbColumns, row, 1);
	++row;

	btnCancel = new QPushButton(i18n("Cancel"));
	btnCancel->setFlat(true);
	addWidget(btnCancel, row, 0);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(exit()));
	btnOk = new QPushButton(i18n("OK"));
	btnOk->setFlat(true);
	addWidget(btnOk, row, 1);
	connect(btnOk, SIGNAL(clicked()), this, SLOT(addTable()));
}

AddTable::~AddTable()
{
	delete btnCancel;
	delete btnOk;
	delete lblRows;
	delete lblColumns;
	delete sbRows;
	delete sbColumns;
}

void AddTable::exit()
{
	delete this;
}

void AddTable::addTable()
{
	QString html = "<table border=\"0.5\" cellspacing=\"0\" cellpadding=\"2\">";
	for (int rows = 0; rows < sbRows->value(); ++rows)
	{
		html += "<tr>";
		for (int columns = 0; columns < sbColumns->value(); ++columns)
			html += "<td>&nbsp;&nbsp;</td>";
		html += "</tr>";
	}
	html += "</table>";
	emit addedTable(html);
}




