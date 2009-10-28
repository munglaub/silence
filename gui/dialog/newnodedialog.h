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

#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include "data/node/abstractnodecontent.h"
#include "gui/widget/labelwidget.h"
#include "gui/widget/syntaxbox.h"
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>


class NewNodeDialog : public QDialog
{
	Q_OBJECT

	public:
		NewNodeDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~NewNodeDialog();

		QString getCaption() const;
		AbstractNodeContent* getContent() const;
		QStringList getLabels() const;

	private slots:
		void indexChanged(int index);

	private:
		QVBoxLayout *baselayout;

		QFormLayout *namelayout;
		QLineEdit *nameedit;

		QGridLayout *typelayout;
		QLabel *lbltype;
		QComboBox *typebox;
		SyntaxBox *syntaxbox;

		// labels
		LabelWidget *labelwidget;

		// butons
		QPushButton *cancel,
					*ok;
		QGridLayout *buttonlayout;
};

#endif // NEWNODEDIALOG_H


