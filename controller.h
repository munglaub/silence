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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "data/datastore.h"
#include "gui/contentview.h"
#include "gui/editmenu.h"
#include "gui/infosidebar.h"
#include "gui/nodepropertywidget.h"
#include "gui/statusbar.h"
#include "gui/treeview.h"


class Controller
{
	public:
		~Controller();
		static Controller* create();

		void setContentView(ContentView* contentview);
		ContentView* getContentView() const;

		void setInfoSidebar(InfoSidebar* infosidebar);
		InfoSidebar* getInfoSidebar() const;
		
		void setTreeView(TreeView* treeview);
		TreeView* getTreeView() const;
		
		void setStatusBar(StatusBar* statusbar);
		StatusBar* getStatusBar() const;

		void setNodePropertyWidget(NodePropertyWidget *nodepropertywidget);
		NodePropertyWidget* getNodePropertyWidget() const;

		void setEditMenu(EditMenu *editmenu);
		EditMenu* getEditMenu() const;

		DataStore* getDataStore();

	protected:
		Controller();

	private:
		static Controller *controller;
		
		ContentView *contentview;
		InfoSidebar *infosidebar;
		TreeView *treeview;
		StatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;
		EditMenu *editmenu;

		DataStore *datastore;
};

#endif // CONTROLLER_H

