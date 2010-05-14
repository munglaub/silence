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


/*!\class NewLinkDialog
 * \brief A dialog to create a link.
 *
 * A dialog to create links to other nodes, websites or files.
 *
 * \author Manuel Unglaub
 */
class NewLinkDialog : public QDialog
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the NewLinkDialog which is a child of parent and has the provided window flags.
		 *
		 * \param parent The parent of this NewLinkDialog.
		 * \param f The window flags of this NewLinkDialog.
		 */
		NewLinkDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~NewLinkDialog();

		/*!
		 * Provide the NewLinkDialog with a link text.
		 *
		 * \param text The link text.
		 */
		void setLinkText(QString text);

		/*!
		 * Get the link text form the NewLinkDialog.
		 *
		 * \return The link text.
		 */
		QString getLinkText();

		/*!
		 * Get the url of the link.
		 *
		 * \return The url of the link.
		 */
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


