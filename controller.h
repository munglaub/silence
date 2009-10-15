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

#include "persistence/datastore.h"
#include "gui/menu/editmenu.h"
#include "gui/sidebar/infosidebar.h"
#include "gui/sidebar/nodepropertywidget.h"
#include "gui/sidebar/searchnodesidebar.h"
#include "gui/sidebar/treeview.h"
#include "gui/statusbar.h"
#include "gui/view/contentview.h"
#include "gui/view/richtextedit.h"
#include "gui/view/textedit.h"
#include "gui/view/welcomeview.h"


class Controller
{
	public:
		~Controller();
		static Controller* create();

		void setContentView(ContentView* contentview);
		ContentView* getContentView() const;

		WelcomeView* getWelcomeView();
		TextEdit* getTextEdit();
		RichTextEdit* getRichTextEdit();

		void setInfoSidebar(InfoSidebar* infosidebar);
		InfoSidebar* getInfoSidebar() const;

		void setSearchNodeSidebar(SearchNodeSidebar* searchnodesidebar);
		SearchNodeSidebar* getSearchNodeSidebar() const;

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
		WelcomeView *welcomeview;
		TextEdit *textedit;
		RichTextEdit *richtextedit;
		InfoSidebar *infosidebar;
		SearchNodeSidebar *searchsidebar;
		TreeView *treeview;
		StatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;
		EditMenu *editmenu;

		DataStore *datastore;
};

#endif // CONTROLLER_H

