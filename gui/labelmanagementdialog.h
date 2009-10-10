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

#ifndef LABELMANAGEMENTDIALOG_H
#define LABELMANAGEMENTDIALOG_H

#include "node/labelmodel.h"
#include <QAction>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <QTreeView>


class LabelManagementDialog : public QDialog
{
	Q_OBJECT

	public:
		LabelManagementDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~LabelManagementDialog();

	private slots:
		void showTreeContextMenu();
		void addLabel();
		void addRow();
		void addSublabel();
		void removeLabel();
		void selectItem();

	private:
		QGridLayout *layout;
		QToolBar *toolbar;
		QAction *addRowAction,
				*addChildAction,
				*removeAction;
		QTreeView *tree;
		LabelModel *model;
		QPushButton *closeBtn;

		// InputFrame
		QGroupBox *inputFrame;
		QGridLayout *inputLayout;
		QLineEdit *inputEdit;
		QPushButton *okBtn,
					*cancelInputBtn;

		// DeleteFrame
		QGroupBox *deleteFrame;
		QGridLayout *deleteLayout;
		QLabel	*icon,
				*messageLbl;
		QPushButton *yesBtn,
					*noBtn;

		QModelIndex newLabelParent;
		int newLabelRow;

		QWidget* createInputFrame();
		QWidget* createDeleteFrame();
};

#endif // LABELMANAGEMENTDIALOG_H

