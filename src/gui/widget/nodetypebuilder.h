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

#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "src/data/node/customnodeitem.h"
#include "src/data/node/customnodetypedefinition.h"
#include "src/gui/widget/customnodeelement.h"


/*!\class NodeTypeBuilder
 * \brief Create custom node types.
 *
 * Provides a widget to create custom node types. It takes a CustomNodeTypeDefinition and provides a GUI to modify it.
 *
 * \author Manuel Unglaub
 */
class NodeTypeBuilder : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NodeTypeBuilder.
		 */
		NodeTypeBuilder();

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NodeTypeBuilder();

		/*!
		 * Make this widget visible and provide it with a CustomNodeTypeDefinition to modify it.
		 * \param def The CustomNodeTypeDefinition to modify.
		 */
		void show(CustomNodeTypeDefinition *def);

		/*!
		 * Get the modified CustomNodeTypeDefinition.
		 * \return A pointer to the modified CustomNodeTypeDefinition.
		 */
		CustomNodeTypeDefinition* getCustomNodeTypeDefinition();

	signals:
		/*!
		 * The close button was clicked.
		 */
		void close();

	private slots:
		void onClose();
		void addElement();
		void updateBtnAddElement();
		void removeItem(CustomNodeElement* element, CustomNodeItem *item);

	private:
		QVBoxLayout *layout,
					*prevlayout;
		QFormLayout *buildlayout;
		QGroupBox	*buildpane,
					*prevpane;
		QLineEdit *leElementCaption;
		QComboBox *elementTypes;
		QPushButton *btnAddElement,
					*btnClose;

		CustomNodeTypeDefinition *def;
		QList<CustomNodeElement*> elements;

		void clearPrevlayout();
		void addElementToPrevlayout(CustomNodeItem *item);
};

#endif // NODETYPEBUILDER_H

