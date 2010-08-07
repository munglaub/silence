/*
 * Silence
 *
 * Copyright (C) 2010 Manuel Unglaub
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

#ifndef NODETYPEMANAGER_H
#define NODETYPEMANAGER_H

#include <QVBoxLayout>
#include <QWidget>
#include "src/gui/widget/inputwidget.h"
#include "src/gui/widget/nodetypebuilder.h"
#include "src/gui/widget/nodetypespanel.h"


/*!\class NodeTypeManager
 * \brief Manage custom node types.
 *
 * This class can add, edit and delete custom node types. It uses a NodeTypesPanel to show the the custom node types and a NodeTypeBuilder to add and edit them.
 *
 * \author Manuel Unglaub
 */
class NodeTypeManager : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NodeTypeManager.
		 */
		NodeTypeManager();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NodeTypeManager();
	
	signals:
		/*!
		 * Indicates that the user wants to close this view.
		 * \param itself This NodeTypeManager.
		 */
		void exit(QWidget *itself);

	private slots:
		void sendExit();
		void showInputWidget();
		void addNodeType();
		void deleteNodeType(QString name);
		void showNodeTypeBuilder(QString customNodeTypeName);
		void hideNodeTypeBuilder();

	private:
		QVBoxLayout *layout;
		NodeTypesPanel *nodetypespanel;
		InputWidget *inputwidget;
		NodeTypeBuilder *nodetypebuilder;

};

#endif // NODETYPEMANAGER_H

