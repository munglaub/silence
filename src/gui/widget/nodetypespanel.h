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

#ifndef NODETYPESPANEL_H
#define NODETYPESPANEL_H

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>


/*!\class NodeTypesPanel
 * \brief Lists the custom node types.
 *
 * Provides a list of custom node types and buttons to add, edit and delete them.
 *
 * \author Manuel Unglaub
 */
class NodeTypesPanel : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NodeTypesPanel.
		 */
		NodeTypesPanel();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NodeTypesPanel();

		/*!
		 * Triggers an update of the list of custom node types.
		 */
		void updateTypeList();
	
	signals:
		/*!
		 * The close button was clicked.
		 */
		void exit();

		/*!
		 * The user wants to create a new type.
		 */
		void addNodeType();

		/*!
		 * The user wants to edit a type.
		 * \param name The type the user wants to edit.
		 */
		void editNodeType(QString name);

		/*!
		 * The user wants to delete a type.
		 * \param name The type the user wants to delete.
		 */
		void deleteNodeType(QString name);
	
	private slots:
		void sendExit();
		void addType();
		void editType();
		void deleteType();
		void updateButtons();

	private:
		QGridLayout *layout;
		QLabel *caption;
		QListWidget *typelist;
		QPushButton *btnAdd,
					*btnEdit,
					*btnDelete,
					*btnExit;

};

#endif // NODETYPESPANEL_H

