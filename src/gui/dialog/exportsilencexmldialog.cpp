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

 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/gui/dialog/exportsilencexmldialog.h"
#include <klocalizedstring.h>
#include "src/data/model/treemodel.h"
#include <QGridLayout>
#include <kfiledialog.h>
#include <QRadioButton>
#include <QPushButton>
#include <QTreeView>


ExportSilenceXmlDialog::ExportSilenceXmlDialog(QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	QGridLayout *layout = new QGridLayout;
	int row = 0;

	QRadioButton *rbExportAll = new QRadioButton(i18n("Export all"));
	rbExportAll->setChecked(true);
	layout->addWidget(rbExportAll, row, 0);
	++row;

	QRadioButton *rbExportPartial = new QRadioButton(i18n("Export partial"));
	layout->addWidget(rbExportPartial, row, 0);
	++row;

	QTreeView *treeview = new QTreeView;
	TreeModel *treemodel = new TreeModel;
	treeview->setModel(treemodel);
	treeview->setSelectionBehavior(QAbstractItemView::SelectItems);
	treeview->setEnabled(false);
	layout->addWidget(treeview, row, 1);
	++row;

	ledPath = new QLineEdit;
	layout->addWidget(ledPath, row, 1);

	QPushButton *btnSelectFile = new QPushButton(i18n("Select File"));
	btnSelectFile->setMinimumWidth(100);
	connect(btnSelectFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	layout->addWidget(btnSelectFile, row, 2, 1, 1, Qt::AlignLeft);
	++row;


	QPushButton *btnAbort = new QPushButton(i18n("Close"));
	btnAbort->setMinimumWidth(100);
	connect(btnAbort, SIGNAL(clicked()), this, SLOT(abort()));
	layout->addWidget(btnAbort, row, 0);

	QPushButton *btnExport = new QPushButton(i18n("Export"));
	btnExport->setMinimumWidth(100);
	connect(btnExport, SIGNAL(clicked()), this, SLOT(exportXml()));
	layout->addWidget(btnExport, row, 2, 1, 1, Qt::AlignLeft);

	setLayout(layout);

	connect(rbExportPartial, SIGNAL(toggled(bool)), treeview, SLOT(setEnabled(bool)));
}

ExportSilenceXmlDialog::~ExportSilenceXmlDialog()
{
	// TODO: implement
}

void ExportSilenceXmlDialog::abort(){
	emit exit(this);
}

void ExportSilenceXmlDialog::exportXml(){
	// get root node (selected or full)
	// check for valid file
	// tell the xmldatastore to write it to the file


	emit exit(this);
}

void ExportSilenceXmlDialog::selectFile(){
	QString fileName = KFileDialog::getSaveFileName(KUrl(), "*.xml | " + i18n("Silence XML file"), this, i18n("Select File"));
	ledPath->setText(fileName);

}



