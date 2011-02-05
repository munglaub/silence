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

#include <kfiledialog.h>
#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/gui/dialog/exportsilencexmldialog.h"
#include "src/persistence/xmldatastore.h"


ExportSilenceXmlDialog::ExportSilenceXmlDialog(QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	layout = new QGridLayout;
	int row = 0;

	caption = new QLabel("<h2>" + i18n("Export Silence XML-File") + "</h2>");
	layout->addWidget(caption, row, 0);
	++row;

	hint = new QLabel("<i>(" + i18n("Export data in the Silence format.") + ")</i>");
	layout->addWidget(hint, row, 0);
	++row;

	rbExportAll = new QRadioButton(i18n("Export all"));
	rbExportAll->setChecked(true);
	layout->addWidget(rbExportAll, row, 0);
	++row;

	rbExportPartial = new QRadioButton(i18n("Export partial"));
	layout->addWidget(rbExportPartial, row, 0, 1, 1, Qt::AlignTop);

	treeview = new QTreeView;
	treemodel = new TreeModel;
	treeview->setModel(treemodel);
	treeview->setSelectionBehavior(QAbstractItemView::SelectItems);
	treeview->setEnabled(false);
	layout->addWidget(treeview, row, 1);
	++row;

	pathCaption = new QLabel(i18n("Exportfile"));
	layout->addWidget(pathCaption, row, 0, 1, 1, Qt::AlignRight);

	ledPath = new QLineEdit;
	layout->addWidget(ledPath, row, 1);

	btnSelectFile = new QPushButton(i18n("Select File"));
	btnSelectFile->setMinimumWidth(100);
	connect(btnSelectFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	layout->addWidget(btnSelectFile, row, 2, 1, 1, Qt::AlignLeft);
	++row;


	btnAbort = new QPushButton(i18n("Close"));
	btnAbort->setMinimumWidth(100);
	connect(btnAbort, SIGNAL(clicked()), this, SLOT(abort()));
	layout->addWidget(btnAbort, row, 0, 1, 1, Qt::AlignLeft);

	btnExport = new QPushButton(i18n("Export"));
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
	if (ledPath->text().isEmpty()){
		hint->setText("<font color=\"#FF0000\">" + i18n("Select a file to export the data.") + "</font>");
		pathCaption->setText("<font color=\"#FF0000\">" + pathCaption->text() + "</font>");
		return;
	}

	Node *exportRoot;
	if (rbExportAll->isChecked()){
		exportRoot = Controller::create()->getDataStore()->getRootNode();
	} else {
		QModelIndex index = treeview->selectionModel()->currentIndex();
		exportRoot = treemodel->getItem(index);
	}
	XmlDataStore::writeToXmlFile(ledPath->text(), exportRoot);

	emit exit(this);
}

void ExportSilenceXmlDialog::selectFile(){
	QString fileName = KFileDialog::getSaveFileName(KUrl(), "*.xml | " + i18n("Silence XML-File"), this, i18n("Select File"));
	ledPath->setText(fileName);

}



