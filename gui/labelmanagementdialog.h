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

#include <QDialog>
#include <QGridLayout>
#include <QToolBar>
#include <QTreeView>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QAction>
#include <QLabel>


class LabelManagementDialog : public QDialog
{
	public:
		LabelManagementDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~LabelManagementDialog();

	private:
		QGridLayout *layout;
		QToolBar *toolbar;
		QAction *addRowAction,
				*addChildAction,
				*removeAction;
		QTreeView *tree;
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

		QWidget* createInputFrame();
		QWidget* createDeleteFrame();
};

#endif // LABELMANAGEMENTDIALOG_H

