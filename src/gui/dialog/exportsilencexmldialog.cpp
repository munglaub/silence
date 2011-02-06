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


ExportSilenceXmlDialog::ExportSilenceXmlDialog(ExportSilenceXmlDialog::Type type, QWidget *parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	this->type = type;

	layout = new QGridLayout;
	int row = 0;

	caption = new QLabel;
	layout->addWidget(caption, row, 0);
	++row;

	hint = new QLabel;
	layout->addWidget(hint, row, 0);
	++row;

	rbExportAll = new QRadioButton;
	rbExportAll->setChecked(true);
	layout->addWidget(rbExportAll, row, 0);
	++row;

	rbExportPartial = new QRadioButton;
	layout->addWidget(rbExportPartial, row, 0, 1, 1, Qt::AlignTop);

	treeview = new QTreeView;
	treemodel = new TreeModel;
	treeview->setModel(treemodel);
	treeview->setSelectionBehavior(QAbstractItemView::SelectItems);
	treeview->setEnabled(false);
	layout->addWidget(treeview, row, 1);
	++row;

	pathCaption = new QLabel;
	layout->addWidget(pathCaption, row, 0, 1, 1, Qt::AlignRight);

	ledPath = new QLineEdit;
	layout->addWidget(ledPath, row, 1);

	btnSelectFile = new QPushButton(i18n("Select File"));
	btnSelectFile->setMinimumWidth(100);
	connect(btnSelectFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	layout->addWidget(btnSelectFile, row, 2, 1, 1, Qt::AlignLeft);
	++row;


	btnAbort = new QPushButton;
	btnAbort->setMinimumWidth(100);
	connect(btnAbort, SIGNAL(clicked()), this, SLOT(abort()));
	layout->addWidget(btnAbort, row, 0, 1, 1, Qt::AlignLeft);

	btnExport = new QPushButton;
	btnExport->setMinimumWidth(100);
	connect(btnExport, SIGNAL(clicked()), this, SLOT(execute()));
	layout->addWidget(btnExport, row, 2, 1, 1, Qt::AlignLeft);

	setLayout(layout);

	connect(rbExportPartial, SIGNAL(toggled(bool)), treeview, SLOT(setEnabled(bool)));
}

ExportSilenceXmlDialog::~ExportSilenceXmlDialog()
{
	// TODO: implement
}

void ExportSilenceXmlDialog::setCaption(QString caption){
	this->caption->setText("<h2>" + caption + "</h2>");
}

void ExportSilenceXmlDialog::setHint(QString hint){
	this->hint->setText("<i>(" + hint + ")</i>");
}

void ExportSilenceXmlDialog::setOptions(QString full, QString partial){
	rbExportAll->setText(full);
	rbExportPartial->setText(partial);
}

void ExportSilenceXmlDialog::setPathCaption(QString pathCaption){
	this->pathCaption->setText(pathCaption);
}

void ExportSilenceXmlDialog::setButtonCaptions(QString abort, QString execute){
	btnAbort->setText(abort);
	btnExport->setText(execute);
}

void ExportSilenceXmlDialog::setErrorMessage(QString errorMessage){
	this->errorMessage = errorMessage;
}

void ExportSilenceXmlDialog::abort(){
	emit exit(this);
}

void ExportSilenceXmlDialog::execute(){
	if (ledPath->text().isEmpty()){
		hint->setText("<font color=\"#FF0000\">" + errorMessage + "</font>");
		pathCaption->setText("<font color=\"#FF0000\">" + pathCaption->text() + "</font>");
		return;
	}

	Node *node;
	if (rbExportAll->isChecked()){
		node = Controller::create()->getDataStore()->getRootNode();
	} else {
		QModelIndex index = treeview->selectionModel()->currentIndex();
		node = treemodel->getItem(index);
	}
	emit executed(node, ledPath->text());

	emit exit(this);
}

void ExportSilenceXmlDialog::selectFile(){
	QString fileName;
	if (type == ExportSilenceXmlDialog::Export){
		fileName = KFileDialog::getSaveFileName(KUrl(), "*.xml | " + i18n("Silence XML-File"), this, i18n("Select File"));
	} else {
		fileName = KFileDialog::getOpenFileName(KUrl(), "*.xml | " + i18n("Silence XML-File"), this, i18n("Select File"));
	}
	ledPath->setText(fileName);
}



