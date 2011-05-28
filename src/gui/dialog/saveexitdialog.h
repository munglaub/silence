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
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>

//TODO: docu
class SaveExitDialog : public QDialog
{
	Q_OBJECT

	public:
		SaveExitDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
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

		void setupGui();
		void addUnsavedNodes();
};

#endif // SAVEEXITDIALOG_H

