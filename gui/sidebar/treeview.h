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

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "data/model/treemodel.h"
#include "gui/sidebar/nodepropertywidget.h"
#include <QDockWidget>
#include <QFrame>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QList>
#include <QLabel>
#include <QGroupBox>


class TreeView : public QDockWidget
{
	Q_OBJECT

	public:
		TreeView(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~TreeView();
		QList<QAction*>* getNodeActions() const;
		QTreeView* getTree();

	public slots:
		void updateActions();
		void selectItem();

	private slots:
		void addRow();
		void addChild();
		void removeTreeItem();
		void showTreeContextMenu();
		void nodeDropped(QModelIndex index);
                
	private:
		QTreeView *tree;
		TreeModel *model;

		QToolBar *toolbar;
		QAction *addRowAction,
				*addChildAction,
				*removeAction,
				*propertyAction;

		QLabel	*question,
				*icon;
		QPushButton *yesButton,
					*noButton;

		QFrame *frame;
		QGroupBox *questionFrame;

		QVBoxLayout *layout;
		QGridLayout *questionLayout;

		void addNode(QModelIndex &index, int row);
};

#endif // TREEVIEW_H

