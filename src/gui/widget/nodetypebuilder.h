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

#ifndef NODETYPEBUILDER_H
#define NODETYPEBUILDER_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include "src/data/node/customnodetypedefinition.h"


//TODO: documentation
class NodeTypeBuilder : public QWidget
{
	Q_OBJECT

	public:
		NodeTypeBuilder();
		~NodeTypeBuilder();

		void show(CustomNodeTypeDefinition *def);

	signals:
		void close();

	private slots:
		void onClose();
		void addElement();
		void updateBtnAddElement();

	private:
		QVBoxLayout *layout,
					*prevlayout;
		QLabel	*lblElementCaption,
				*lblElementTypes;
		QGroupBox	*buildpane,
					*prevpane;
		QGridLayout *buildlayout;
		QLineEdit *leElementCaption;
		QListWidget *elementTypes;
		QPushButton *btnAddElement;


};

#endif // NODETYPEBUILDER_H

