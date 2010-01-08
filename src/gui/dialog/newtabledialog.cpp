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

#include "src/gui/dialog/newtabledialog.h"


NewTableDialog::NewTableDialog(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f)
{
	setWindowTitle(tr("New Table"));
	resize(300, 100);

	layout = new QGridLayout;
	int row = 0;

	lblRows = new QLabel(tr("Rows"));
	layout->addWidget(lblRows, row, 0);
	ledRows = new QLineEdit;
	layout->addWidget(ledRows, row, 1);
	++row;

	lblColumns = new QLabel(tr("Columns"));
	layout->addWidget(lblColumns, row, 0);
	ledColumns = new QLineEdit;
	layout->addWidget(ledColumns, row, 1);
	++row;

	btnCancel = new QPushButton(tr("Cancel"));
	layout->addWidget(btnCancel, row, 0, 1, 1, Qt::AlignLeft);
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
	btnOk = new QPushButton(tr("OK"));
	btnOk->setDefault(true);
	layout->addWidget(btnOk, row, 1, 1, 1, Qt::AlignRight);
	connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));

	setLayout(layout);
}

NewTableDialog::~NewTableDialog()
{
	delete btnOk;
	delete btnCancel;
	delete ledColumns;
	delete ledRows;
	delete lblColumns;
	delete lblRows;
	delete layout;
}

int NewTableDialog::getRowCount()
{
	return ledRows->text().toInt();
}

int NewTableDialog::getColumnCount()
{
	return ledColumns->text().toInt();
}


