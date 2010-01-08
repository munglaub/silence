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

#ifndef LABELLIST_H
#define LABELLIST_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QAction>


class LabelList : public QFrame
{
	Q_OBJECT

	public:
		LabelList(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~LabelList();

	signals:
		void addedLabel(QString label);
		void removedLabel(QString label);
		void addedBannedLabel(QString label);
		void removedBannedLabel(QString label);
		void clearLabels();
		void clearBannedLabels();

	public slots:
		void update();

	private slots:
		void toggleVisibility();
		void showContextMenu();
		void addLabel();
		void addBannedLabel();
		void clear();

	private:
		bool showOptions;
		QGridLayout *layout;
		QLabel *title;
		QPushButton *showBtn;
		QListWidget *list;

		QAction *addLabelAction,
				*addBannedLabelAction,
				*clearAction;

		void fillList();
		void setupActions();

};

#endif // LABELLIST_H


