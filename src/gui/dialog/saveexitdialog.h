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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SAVEEXITDIALOG_H
#define SAVEEXITDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>
#include <QVBoxLayout>
#include "src/data/node/node.h"


/*!\class SaveExitDialog
 * \brief A dialog giving the user the chance to save the unsaved nodes.
 *
 * This dialog should be shown if the user is trying to close this application while there are unsaved nodes. It gives
 * the user the chance to save these unsaved nodes or to go back to the nodes without closing the applicaiton.
 *
 * \author Manuel Unglaub
 */
class SaveExitDialog : public QDialog
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the SaveExitDialog which is a child of parent and has the provided WindowFlags.
		 * \param parent The parent of this SaveExitDialog.
		 * \param f Tje WindowFlags of this SaveExitDialog.
		 */
		SaveExitDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~SaveExitDialog();

	private slots:
		void save();

	private:
		QVBoxLayout *layout;
		QTreeWidget *list;
		QHBoxLayout *btnLayout;
		QPushButton *btnDontSave,
					*btnSave,
					*btnDontClose;

		QHash<QTreeWidgetItem*, Node*> items;

		void setupGui();
		void addUnsavedNodes();
};

#endif // SAVEEXITDIALOG_H

