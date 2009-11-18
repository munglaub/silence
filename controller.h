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
#include "persistence/abstractdatastore.h"
#include "persistence/xmldatastore.h"


/*!\class Controller
 * \brief Provides access to various parts of the application.
 *
 * The Controller provides access to objects needed in different parts of
 * the application. It is a Singelton and can be created with the
 * static create() function.
 *
 * Some classes should have only one instance which is managed by the
 * Controller. These classes are WelcomeView, TextEdit, DataStore
 * and RichTextEdit.
 * To use these classes you can use the get-methods of the Controller.
 *
 * \author Manuel Unglaub
 */
class Controller
{
	public:
		/*! The destructor.
		 * Destroys the datastore.
		 */
		~Controller();

		/*!
		 * This function creates a instance of the Controller if there is not alredy one.
		 * \return A instance of the Controller.
		 */
		static Controller* create();

		/*!
		 * This function provides the Controller with a pointer of the ContentView.
		 * \param contentview A pointer to the ContentView.
		 */
		void setContentView(ContentView* contentview);
		/*!
		 * Get a pointer of the ContentView.
		 * \return A pointer of the ContentView or 0 if it was not set.
		 */
		ContentView* getContentView() const;

		/*!
		 * Get a pointer to the WelcomeView. The Controller will manage the
		 * WelcomeView, that means it will create and destroy it.
		 * \return A pointer to the WelcomeView.
		 */
		WelcomeView* getWelcomeView();
		/*!
		 * Get a pointer to the TextEdit. The Controller will manage the
		 * TextEdit, that means it will create and destroy it.
		 * \return A pointer to the TextEdit.
		 */

		TextEdit* getTextEdit();

		/*!
		 * Get a pointer to the RichTextEdit. The Controller will manage the
		 * RichTextEdit, that means it will create and destroy it.
		 * \return A pointer to the RichTextEdit.
		 */
		RichTextEdit* getRichTextEdit();

		/*!
		 * Get a pointer to the datastore. The Controller will manage the
		 * datastore, that means it will create and destroy it. The datastore is the backend responsible for persisting the data. The following datastores are availlable: XmlDataStore
		 * \return A pointer to the AbstractDataStore.
		 */
		AbstractDataStore* getDataStore();

		/*!
		 * This function provides the Controller with a pointer to the InfoSidebar.
		 * \param infosidebar A pointer to the InfoSidebar
		 */
		void setInfoSidebar(InfoSidebar* infosidebar);

		/*!
		 * Get a pointer to the InfoSidebar.
		 * \return A pointer to the InfoSidebar or 0 if it was not set.
		 */
		InfoSidebar* getInfoSidebar() const;

		/*!
		 * This function provides the Controller with a pointer to the SearchNodeSidebar.
		 * \param searchnodesidebar A pointer to the SearchNodeSidebar.
		 */
		void setSearchNodeSidebar(SearchNodeSidebar* searchnodesidebar);

		/*!
		 * Get a pointer to the SearchNodeSidebar.
		 * \return A pointer to the SearchNodeSidebar or 0 if it was not set.
		 */
		SearchNodeSidebar* getSearchNodeSidebar() const;

		/*!
		 * This function provides the Controller with a pointer to the TreeView.
		 * \param treeview A pointer to the TreeView.
		 */
		void setTreeView(TreeView* treeview);

		/*!
		 * Get a pointer to the TreeView.
		 * \return A pointer to the TreeView or 0 if it was not set.
		 */
		TreeView* getTreeView() const;
		
		/*!
		 * This function provides the Controller with a pointer to the StatusBar.
		 * \param statusbar A pointer to the StatusBar.
		 */
		void setStatusBar(StatusBar* statusbar);

		/*!
		 * Get a pointer to the StatusBar.
		 * \return A pointer to the StatusBar or 0 if it was not set.
		 */
		StatusBar* getStatusBar() const;

		/*!
		 * This function provides the Controller with a pointer to the NodePropertyWidget.
		 * \param nodepropertywidget A pointer to the NodePropertyWidget.
		 */
		void setNodePropertyWidget(NodePropertyWidget *nodepropertywidget);

		/*!
		 * Get a pointer to the NodePropertyWidget.
		 * \return A pointer to the NodePropertyWidget or 0 if it was not set.
		 */
		NodePropertyWidget* getNodePropertyWidget() const;

		/*!
		 * This function provides the Controller with a pointer to the EditMenu.
		 * \param editmenu A pointer to the EditMenu.
		 */
		void setEditMenu(EditMenu *editmenu);

		/*!
		 * Get a pointer to the EditMenu.
		 * \return A pointer to the EditMenu or 0 if it was not set.
		 */
		EditMenu* getEditMenu() const;


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

		AbstractDataStore *datastore;
};

#endif // CONTROLLER_H

