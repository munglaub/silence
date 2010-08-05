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

#include <QWidget>
#include <QVBoxLayout>
#include "src/gui/widget/nodetypespanel.h"
#include "src/gui/widget/inputwidget.h"
#include "src/gui/widget/nodetypebuilder.h"


//TODO: documentation
class NodeTypeManager : public QWidget
{
	Q_OBJECT

	public:
		NodeTypeManager();
		~NodeTypeManager();
	
	signals:
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

