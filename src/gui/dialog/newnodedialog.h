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

#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include <kcombobox.h>
#include <klineedit.h>
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include "src/data/node/abstractnodecontent.h"
#include "src/gui/widget/labelwidget.h"
#include "src/gui/widget/syntaxbox.h"


/*!\class NewNodeDialog
 * \brief A dialog to create a new node.
 *
 * This dialog provides the user with a GUI to create a new node. The dialog does not create a node, it only provides the necessary elements to create one.
 *
 * \author Manuel Unglaub
 */
class NewNodeDialog : public QDialog
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NewNodeDialog which is a child of parent.
		 * \param parent The parent of this NewNodeDialog.
		 * \param f The dialog flags f are passed on to the QDialog constructor.
		 */
		explicit NewNodeDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NewNodeDialog();

		/*!
		 * Get the caption the user entered at the dialog for the new node.
		 * \return The caption the user entered.
		 */
		QString getCaption() const;

		/*!
		 * Get the content the user selected at the dialog for the new node.
		 * \return The content the user selected.
		 */
		AbstractNodeContent* getContent() const;

		/*!
		 * Get the labels the user selected for the new node.
		 * \return A QStringList which contains the selected labels.
		 */
		QStringList getLabels() const;

	private slots:
		void indexChanged(int index);

	private:
		QVBoxLayout *baselayout;

		QFormLayout *namelayout;
		KLineEdit *nameedit;

		QGridLayout *typelayout;
		QLabel *lbltype;
		KComboBox *typebox;
		SyntaxBox *syntaxbox;

		LabelWidget *labelwidget;

		QPushButton *cancel,
					*ok;
		QGridLayout *buttonlayout;
};

#endif // NEWNODEDIALOG_H


