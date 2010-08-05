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

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>


//TODO: documentation
class NodeTypesPanel : public QWidget
{
	Q_OBJECT

	public:
		NodeTypesPanel();
		~NodeTypesPanel();

		void updateTypeList();
	
	signals:
		void exit();
		void addNodeType();
		void editNodeType(QString name);
		void deleteNodeType(QString name);
	
	private slots:
		void sendExit();
		void addType();
		void editType();
		void deleteType();
		void updateButtons();

	private:
		QGridLayout *layout;
		QListWidget *typelist;
		QPushButton *btnAdd,
					*btnEdit,
					*btnDelete,
					*btnExit;

};

#endif // NODETYPESPANEL_H

