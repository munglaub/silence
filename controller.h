#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gui/contentview.h"
#include "gui/infosidebar.h"
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

	protected:
		Controller();

	private:
		static Controller *controller;
		
		ContentView *contentview;
		InfoSidebar *infosidebar;
		TreeView *treeview;
		// textedit
		// richtextedit
		// menues
};

#endif // CONTROLLER_H

