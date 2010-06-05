/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
 * Copyright (C) 2009, 2010 Yves Adler <yves.adler@googlemail.com>
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

#include "src/data/model/filtermodel.h"
#include "src/data/model/listproxymodel.h"
#include "src/gui/widget/labellist.h"
#include "src/gui/widget/searchnodeoptions.h"
#include <QDockWidget>
#include <QGridLayout>
#include <klineedit.h>
#include <QListView>


/*!\class SearchNodeSidebar
 * \brief A sidebar to search for nodes.
 *
 * The purpose of this SearchNodeSidebar is the ability to search for nodes. It provides a search based on the captions or on the full text of a node. It can restrict the results further by limiting the time period of the last change or the creation date. The contenttype can also be used to refine the search.
 *
 * It uses the ListProxyModel and the FilterModel to find the nodes which are searched for.
 * This widget is allowed to dock at the right and the left docking areas.
 *
 * \authors Yves Adler, Manuel Unglaub
 */
class SearchNodeSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		/*! The constructor
		 *
		 * Constructs a SearchNodeSidebar which is a child of parent and has the provided window flags. The SearchNodeSidebar will be places in the left dock widget area.
		 *
		 * The window title is set to title. This title is used when the SearchNodeSidebar is docked and undocked. It is also used in the context menu provided by MainWindow.
		 * The parameters will be passed to the QDockWidget constructor.
		 * \param title The title of this SearchNodeSidebar.
		 * \param parent The parent of this SearchNodeSidebar.
		 * \param flags The window flags of this SearchNodeSidebar.
		 */
		explicit SearchNodeSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~SearchNodeSidebar();

		/*!
		 * Call to update the list of labels.
		 */
		void updateLabels();

	private slots:
		void selectionChanged(QModelIndex current);

	private:
		ListProxyModel *listProxy;
		FilterModel *filtermodel;

		QGridLayout *layout;
		QFrame	*frame;
		SearchNodeOptions *searchnodeoptions;
		LabelList *labellist;
		QListView *resultList;
		KLineEdit *searchedit;

		void connectOptions();
		void connectLabelList();
};

#endif // SEARCHNODESIDEBAR_H

