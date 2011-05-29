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

#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QVBoxLayout>
#include <QWidget>
#include "src/data/node/abstractnodecontent.h"
#include "src/data/node/node.h"
#include "src/gui/view/abstractcontentview.h"

/*!\class ContentView
 * \brief The central widget of the MainWindow.
 *
 * This ContentView shows the widget providet by an AbstractNodeContent or if not available the WelcomeView.
 *
 * \author Manuel Unglaub
 */
class ContentView : public QWidget
{
	public:
		/*! The constructor.
		 *
		 * Constructs the ContentView which is a child of parent. The initial widget is the WelcomeView.
		 * \param parent The parent of this ContentView.
		 */
		ContentView(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~ContentView();

		/*!
		 * Provide this ContentView with a content to display. The ContentView will show the widget provided by the content of the Node.
		 * \param node The content of this node will be displayed. If it is 0 the WelcomeView will be shown.
		 */
		void setNode(Node *node);

		//TODO: docu
		Node* getNode();
		//TODO: docu
		AbstractContentView* getView();

	private:
		QVBoxLayout *layout;
		AbstractContentView *widget;
		Node *node;
};

#endif // CONTENTVIEW_H


