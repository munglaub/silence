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

#ifndef NEWLINKDIALOG_H
#define NEWLINKDIALOG_H

#include <klineedit.h>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QTreeView>
#include <QUrl>
#include "src/data/model/simpletreemodel.h"


class NewLinkDialog : public QDialog
{
	Q_OBJECT

	public:
		NewLinkDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~NewLinkDialog();

		void setLinkText(QString text);
		QString getLinkText();

		QUrl getUrl();

	private slots:
		void selectFile();

	private:
		QGridLayout *layout;
		QTreeView *tree;
		SimpleTreeModel *model;
		QPushButton *btnCancel,
					*btnOk,
					*btnSelectFile;
		QLabel	*lblLinkText;
		QRadioButton	*rbtnNode,
						*rbtnWebUrl,
						*rbtnFile;
		KLineEdit	*ledLinkText,
					*ledWebUrl,
					*ledFile;

};

#endif // NEWLINKDIALOG_H


