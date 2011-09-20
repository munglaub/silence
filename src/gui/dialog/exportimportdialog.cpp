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
#include "src/gui/dialog/exportimportdialog.h"
#include "src/persistence/xmldatastore.h"


ExportImportDialog::ExportImportDialog(ExportImportDialog::Type type, QWidget *parent, Qt::WindowFlags f)
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

	rbAll = new QRadioButton;
	rbAll->setChecked(true);
	layout->addWidget(rbAll, row, 0);
	++row;

	rbPartial = new QRadioButton;
	layout->addWidget(rbPartial, row, 0, 1, 1, Qt::AlignTop);

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

	btnExecute = new QPushButton;
	btnExecute->setMinimumWidth(100);
	connect(btnExecute, SIGNAL(clicked()), this, SLOT(execute()));
	layout->addWidget(btnExecute, row, 2, 1, 1, Qt::AlignLeft);

	setLayout(layout);

	connect(rbPartial, SIGNAL(toggled(bool)), treeview, SLOT(setEnabled(bool)));

	fileTypeString = "* | " + i18n("All Files");
}

ExportImportDialog::~ExportImportDialog()
{
	delete btnExecute;
	delete btnAbort;
	delete btnSelectFile;
	delete ledPath;
	delete treemodel;
	delete treeview;
	delete pathCaption;
	delete hint;
	delete caption;
	delete layout;
}

void ExportImportDialog::setCaption(QString caption){
	this->caption->setText("<h2>" + caption + "</h2>");
}

void ExportImportDialog::setHint(QString hint){
	this->hint->setText("<i>(" + hint + ")</i>");
}

void ExportImportDialog::setOptions(QString full, QString partial){
	rbAll->setText(full);
	rbPartial->setText(partial);
}

void ExportImportDialog::setPathCaption(QString pathCaption){
	this->pathCaption->setText(pathCaption);
}

void ExportImportDialog::setButtonCaptions(QString abort, QString execute){
	btnAbort->setText(abort);
	btnExecute->setText(execute);
}

void ExportImportDialog::setErrorMessage(QString errorMessage){
	this->errorMessage = errorMessage;
}

void ExportImportDialog::setFileTypeString(QString fileTypeString){
	this->fileTypeString = fileTypeString;
}

void ExportImportDialog::abort(){
	emit exit(this);
}

void ExportImportDialog::execute(){
	if (ledPath->text().isEmpty()){
		hint->setText("<font color=\"#FF0000\">" + errorMessage + "</font>");
		pathCaption->setText("<font color=\"#FF0000\">" + pathCaption->text() + "</font>");
		return;
	}

	Node *node;
	if (rbAll->isChecked()){
		node = Controller::create()->getDataStore()->getRootNode();
	} else {
		QModelIndex index = treeview->selectionModel()->currentIndex();
		node = treemodel->getItem(index);
	}
	emit executed(node, ledPath->text());

	emit exit(this);
}

void ExportImportDialog::selectFile(){
	QString fileName;
	if (type == ExportImportDialog::Export){
		fileName = KFileDialog::getSaveFileName(KUrl(), fileTypeString, this, i18n("Select File"));
	} else {
		fileName = KFileDialog::getOpenFileName(KUrl(), fileTypeString, this, i18n("Select File"));
	}
	ledPath->setText(fileName);
}



