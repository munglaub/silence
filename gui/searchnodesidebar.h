/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler
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

#ifndef SEARCHNODESIDEBAR_H
#define SEARCHNODESIDEBAR_H

#include "node/filtermodel.h"

#include <QDockWidget>
#include <QGridLayout>
#include <QListView>
#include <QLineEdit>


class SearchNodeSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		SearchNodeSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~SearchNodeSidebar();

	private:
		QGridLayout *layout;
		QFrame *frame;

		// search results
		QListView *results;
		FilterModel *filtermodel;

		// search properties:
		QLineEdit *searchedit;
	private slots:
		void selectionChanged(QModelIndex current, QModelIndex previous);
};

#endif // SEARCHNODESIDEBAR_H

