/*
 * Silence
 *
 * Copyright (C) 2009 Yves Adler, Manuel Unglaub
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
#include "node/listproxymodel.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDockWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QRadioButton>


class SearchNodeSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		SearchNodeSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~SearchNodeSidebar();

	private slots:
		void selectionChanged(QModelIndex current);
		void enableCreationDate(bool enabled);
		void enableModificationDate(bool enabled);
		void toggleOptionsVisibility();

	private:
		ListProxyModel *listProxy;
		FilterModel *filtermodel;
		bool showOptions;

		QGridLayout *layout, 
					*optboxlayout,
					*dateboxlayout;
		QFrame	*frame, 
				*datebox;

		QGroupBox *optionbox;
		QRadioButton	*captionBtn,
						*fulltextBtn;
		QCheckBox 	*cbMime,
					*cbCreated,
					*cbModified;
		QDateEdit 	*fromCreated,
					*toCreated,
					*fromModified,
					*toModified;
		QComboBox *mimeCombo;
		QLabel	*clbland,
				*mlbland;

		QListView *resultList;

		QLineEdit *searchedit;
		QPushButton *moreBtn;

		void setupSearchRow();
		void setupSearchOptions();
		void setupSearchDate();
};

#endif // SEARCHNODESIDEBAR_H

