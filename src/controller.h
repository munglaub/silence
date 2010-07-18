/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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

#include "src/gui/mainwindow.h"
#include "src/gui/sidebar/infosidebar.h"
#include "src/gui/sidebar/navigationsidebar.h"
#include "src/gui/sidebar/nodepropertywidget.h"
#include "src/gui/sidebar/searchnodesidebar.h"
#include "src/gui/sidebar/treeview.h"
#include "src/gui/sistatusbar.h"
#include "src/gui/view/contentview.h"
#include "src/gui/view/richtextedit.h"
#include "src/gui/view/textedit.h"
#include "src/gui/view/welcomeview.h"
#include "src/persistence/abstractdatastore.h"
#include "src/persistence/xmldatastore.h"


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
		 * This function provides the Controller with a pointer of the MainWindow.
		 * \param A pointer to the MainWindow.
		 */
		void setMainWindow(MainWindow *mainwindow);

		/*!
		 * Get a pointer of the MainWindow.
		 * \return A pointer to the MainWindow.
		 */
		MainWindow* getMainWindow();

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
		 * This function provides the Controller with a collection of the applications actions.
		 * \param actionCollection The collection of actions of the application.
		 */
		void setActionCollection(KActionCollection *actionCollection);

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
		 * This function provides the Controller with a pointer to the SiStatusBar.
		 * \param statusbar A pointer to the StatusBar.
		 */
		void setStatusBar(SiStatusBar* statusbar);

		/*!
		 * Get a pointer to the StatusBar.
		 * \return A pointer to the StatusBar or 0 if it was not set.
		 */
		SiStatusBar* getStatusBar() const;

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
		 * This function provides the Controller with a pointer to the NavigationSidebar.
		 * \param navigationsidebar A pointer to the NavigationSidebar.
		 */
		void setNavigationSidebar(NavigationSidebar *navigationsidebar);

		/*!
		 * Get a pointer to the NavigationSidebar.
		 * \return A pointer to the NavigationSidebar or 0 if it was not set.
		 */
		NavigationSidebar* getNavigationSidebar() const;


	protected:
		Controller();

	private:
		static Controller *controller;
		
		MainWindow *mainwindow;
		ContentView *contentview;
		WelcomeView *welcomeview;
		TextEdit *textedit;
		RichTextEdit *richtextedit;
		InfoSidebar *infosidebar;
		SearchNodeSidebar *searchsidebar;
		TreeView *treeview;
		SiStatusBar *statusbar;
		NodePropertyWidget *nodepropertywidget;
		NavigationSidebar *navigationsidebar;

		KActionCollection *actionCollection;

		AbstractDataStore *datastore;
};

#endif // CONTROLLER_H

