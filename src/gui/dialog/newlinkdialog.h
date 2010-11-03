/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QTreeView>
#include "src/data/model/simpletreemodel.h"


/*!\class NewLinkDialog
 * \brief A dialog to create a link.
 *
 * A dialog to create links to other nodes, websites or files.
 *
 * \author Manuel Unglaub
 */
class NewLinkDialog : public QGridLayout
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the NewLinkDialog which is a child of parent.
		 *
		 * \param parent The parent of this NewLinkDialog.
		 */
		explicit NewLinkDialog(QWidget *parent = 0);

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

	signals:
		/*!
		 * This signal is emitted when the user clicked the ok button.
		 *
		 * \param link Containing the HTML tag that represents the link.
		 */
		void addedLink(const QString &link);

	public slots:
		/*!
		 * Delete this dialog.
		 */
		void exit();

	private slots:
		void selectFile();
		void addLink();

	private:
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

		QString getLinkText();
		KUrl getUrl();
};

#endif // NEWLINKDIALOG_H


