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

#ifndef EXPORTIMPORTDIALOG_H
#define EXPORTIMPORTDIALOG_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTreeView>
#include "src/data/model/treemodel.h"


/*!\class ExportImportDialog
 * \brief A dialog configurable as import or export dialog.
 *
 * This dialog provides the basic elements to import or export data. It is configurable to serve different needs.
 *
 * \author Manuel Unglaub
 */
class ExportImportDialog : public QFrame
{
	Q_OBJECT

	/*!
	 * This type indicates if the dialog is used for exporting or importing data.
	 */
	public:
		enum Type {
			Import,		/*!< It is an import. */
			Export		/*!< It is an export. */
		};

		/*! The constructor.
		 *
		 * Constructs the ExportImportDialog which is a child of parent. All the captions of the ui elements are blanks. You can set them with the setters.
		 * \param type The type of this ExportImportDialog. Decides if the KFileDialog is used to open a file or to save a file.
		 * \param parent The parent of this ExportImportDialog.
		 * \param f The WindowFlags of this ExportImportDialog.
		 */
		ExportImportDialog(ExportImportDialog::Type type, QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~ExportImportDialog();

		/*!
		 * Set the big caption of this dialog.
		 * \param caption The caption of this dialog.
		 */
		void setCaption(QString caption);

		/*!
		 * Set additional information for the user of this dialog. It will show up right below the Caption.
		 * \param hint A hint for the user of this dialog.
		 */
		void setHint(QString hint);

		/*!
		 * Set the caption of the two radiobuttons. The first one indicates that no node will be selected and the second one allows the user to select a node from the treeview inside this dialog.
		 * \param full The caption of the radiobutton which disables the treeview.
		 * \param partial The caption of the radiobutton which allows the user to select a node from the treeview inside this ExportImportDialog.
		 */
		void setOptions(QString full, QString partial);

		/*!
		 * Set the caption of the QLineEdit where the user should input the path to the file that contains the data for the import or where the exported data will be saved.
		 * \param pathCaption The caption of the QLineEdit with the path to the import/export file.
		 */
		void setPathCaption(QString pathCaption);

		/*!
		 * Set the captions for the buttons to initiate the abort or execute action of this dialog.
		 * \param abort The caption of the abort button.
		 * \param execute The caption of the execute button.
		 */
		void setButtonCaptions(QString abort, QString execute);

		/*!
		 * Set the message that will be shown to the user if no path is entered.
		 * \param errorMessage The message that will be shown to the user if no path is entered.
		 */
		void setErrorMessage(QString errorMessage);

		/*!
		 * Set the string that defines which filetypes are displayed.
		 * Default: "* | All Files"
		 * \param fileTypeString The fileTypeString which will be used when opening the KFileDialog.
		 */
		 void setFileTypeString(QString fileTypeString);
	
	signals:
		/*!
		 * This signal will be emitted when the abort button is clicked.
		 * \param self A pointer to this ExportImportDialog.
		 */
		void exit(ExportImportDialog *self);

		/*!
		 * This signal will be emitted when the execute button is clicked and the path was not empty.
		 * \param root The selected Node.
		 * \param fileName The path to the file to be imported/exportet.
		 */
		void executed(Node *root, QString fileName);
	
	private slots:
		void abort();
		void execute();
		void selectFile();
	
	private:
		ExportImportDialog::Type type;
		QString errorMessage,
				fileTypeString;
		QGridLayout *layout;
		QLabel	*caption,
				*hint,
				*pathCaption;
		QRadioButton	*rbAll,
						*rbPartial;
		QTreeView *treeview;
		TreeModel *treemodel;
		QLineEdit *ledPath;
		QPushButton *btnSelectFile,
					*btnAbort,
					*btnExecute;

};

#endif // EXPORTIMPORTDIALOG_H

