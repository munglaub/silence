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

#ifndef EXPORTSILENCEXMLDIALOG_H
#define EXPORTSILENCEXMLDIALOG_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTreeView>
#include "src/data/model/treemodel.h"


// TODO: docu
class ExportSilenceXmlDialog : public QFrame
{
	Q_OBJECT

	public:
		ExportSilenceXmlDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~ExportSilenceXmlDialog();
	
	signals:
		void exit(ExportSilenceXmlDialog *self);
	
	private slots:
		void abort();
		void exportXml();
		void selectFile();
	
	private:
		QGridLayout *layout;
		QLabel	*caption,
				*hint,
				*pathCaption;
		QRadioButton	*rbExportAll,
						*rbExportPartial;
		QTreeView *treeview;
		TreeModel *treemodel;
		QLineEdit *ledPath;
		QPushButton *btnSelectFile,
					*btnAbort,
					*btnExport;

};

#endif // EXPORTSILENCEXMLDIALOG_H

