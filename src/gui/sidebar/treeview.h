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

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <kaction.h>
#include <QDockWidget>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QList>
#include <QModelIndex>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>
#include "src/data/model/treemodel.h"
#include "src/gui/dialog/newnodedialog.h"
#include "src/gui/sidebar/nodepropertywidget.h"


/*!\class TreeView
 * \brief A sidebar to manage the nodes in a tree structure.
 *
 * The nodes are structured as a tree and the TreeView provides a graphical interface to manage the nodes. It uses the TreeModel to access the data. Also it provides the actions to add, remove and move nodes per drag and drop.
 *
 * This TreeView is allowed to dock at the right and the left docking areas.
 *
 * \author Manuel Unglaub
 */
class TreeView : public QDockWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs a TreeView which is a child of parent and has the providet widow flags. The TreeViw will be placed in the left dock widget area.
		 *
		 * The window title is set to title. This title is used when the TreeView is docked and undocked. It is also used in the context menu provided by MainWindow.
		 * The parameters will be passed to the QDockWidget constructor.
		 * \param title The title of the TreeView.
		 * \param parent The parent of this TreeView.
		 * \param flags The window flags of this TreeView.
		 */
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~TreeView();

		/*!
		 * Get the TreeModel to use it as a source for other models.
		 * \return A pointer to the model of the QTreeView.
		 */
		TreeModel* getTreeModel();

		/*!
		 * Select a node by a given QModelIndex.
		 * \param item The QModelIndex of the node which will be selected.
		 */
		void selectItem(QModelIndex &item);

		/*!
		 * Select a node by a given NodeId.
		 * \param id The NodeId of the node which will be selected.
		 */
		void selectItem(NodeId id);

	public slots:
		/*!
		 * Check the availability of the node related actions and enable or disable them.
		 */
		void updateActions();

		/*!
		 * Provide different parts of the application with the currently selected node.
		 */
		void selectItem();

	signals:
		/*!
		 * This signal is emitted in case a node is selected.
		 * \param node The node which is selected.
		 */
		void nodeSelected(Node* node);

	private slots:
		void addRow();
		void addChild();
		void removeTreeItem();
		void showTreeContextMenu();
		void nodeDropped(QModelIndex index);
		void insertNode(NewNodeDialog *dlg, bool insert);
		void showWelcomeView();
                
	private:
		QTreeView *tree;
		TreeModel *model;

		QToolBar *toolbar;
		KAction *addRowAction,
				*addChildAction,
				*removeAction,
				*propertyAction,
				*welcomeAction;

		QLabel	*question,
				*icon;
		QPushButton *yesButton,
					*noButton;

		QFrame *frame;
		QGroupBox *questionFrame;

		QVBoxLayout *layout;
		QGridLayout *questionLayout;

		void addNode(QModelIndex &index, int row);

		void setupToolbar();
		void setupTree();
		void setupQuestionFrame();
};

#endif // TREEVIEW_H

