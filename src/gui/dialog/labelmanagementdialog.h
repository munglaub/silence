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

#ifndef LABELMANAGEMENTDIALOG_H
#define LABELMANAGEMENTDIALOG_H

#include <QAction>
#include <QEventLoop>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QTreeView>
#include "src/data/model/labelmodel.h"
#include "src/gui/widget/inputwidget.h"


/*!\class LabelManagementDialog
 * \brief A dialog to manage the labels.
 *
 * This dialog should be used to add and remove labels to the system.
 *
 * \author Manuel Unglaub
 */
class LabelManagementDialog : public QFrame
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the LabelManagemetDialog which is a child of parent.
		 * \param parent The parent of this LabelManagementDialog.
		 * \param f The dialog flags f are passed on to the QDialog constructor.
		 */
		explicit LabelManagementDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~LabelManagementDialog();

	signals:
		void exit(LabelManagementDialog *self);

	private slots:
		void showTreeContextMenu();
		void addLabel();
		void addRow();
		void addSublabel();
		void removeLabel();
		void selectItem();
		void updateActions();
		void onClose();

	private:
		QGridLayout *layout;
		QToolBar *toolbar;
		QAction *addRowAction,
				*addChildAction,
				*removeAction;
		QTreeView *tree;
		LabelModel *model;
		QPushButton *closeBtn;

		InputWidget *inputwidget;

		// DeleteFrame
		QGroupBox *deleteFrame;
		QGridLayout *deleteLayout;
		QLabel	*icon,
				*messageLbl;
		QPushButton *yesBtn,
					*noBtn;

		QModelIndex newLabelParent;
		int newLabelRow;

		QWidget* createDeleteFrame();
};

#endif // LABELMANAGEMENTDIALOG_H

