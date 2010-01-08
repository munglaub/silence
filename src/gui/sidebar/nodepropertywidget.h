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

#ifndef NODEPROPERTYWIDGET_H
#define NODEPROPERTYWIDGET_H

#include "src/data/node/node.h"
#include "src/gui/widget/labelwidget.h"
#include "src/gui/widget/syntaxbox.h"
#include <QDockWidget>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>


/*!\class NodePropertyWidget
 * \brief A sidebar to edit informations of a node.
 *
 * The NodePropertyWidget should be used to change the informations of a node. It can change the caption, the labels and the syntax if it has a TextNodeContent.
 *
 * This widget is allowed to dock on all docking areas.
 *
 * \author Manuel Unglaub
 */
class NodePropertyWidget : public QDockWidget
{
	Q_OBJECT
	
	public:
		/*! The constructor.
		 *
		 * Constructs a NodePropertyWidget which is a child of parent and has the provided window flags. The NodePropertyWidget will be paced in the right dock widget area.
		 *
		 * The window title is set to title. This title is used when the NodePropertyWidget is docked and undocked. It is also used in the context menu provided by MainWindow.
		 * The parameters will be passed to the QDockWidget constructor.
		 * \param title The title of this NodePropertyWidget.
		 * \param parent The parent of this NodePropertyWidget.
		 * \param flags The window flags of this NodePropertyWidget.
		 */
		NodePropertyWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NodePropertyWidget();

		/*!
		 * Set a node which will be shown and available for editing.
		 * \param node The node which will be shown.
		 */
		void setNode(Node *node);

		/*!
		 * Use this function to update the labels shown in the labeltab of this NodePropertyWidget. This will be necessary after adding or removing labels from the system.
		 */
		void updateLabels();

	private slots:
		void saveNodeInfo();
		void saveLabels();

	private:
		Node *node;
		QVBoxLayout *layout;
		QFrame *frame;
		QTabWidget *tabwidget;

		// nodeinfotab
		QFormLayout *infolayout;
		QFrame *infoframe;
		QLineEdit *nodeName;
		QLabel *creationdate;
		QLabel *modificationdate;
		QPushButton *applyNodeInfo;
		SyntaxBox *syntaxbox;

		// labeltab
		QGridLayout *labellayout;
		QFrame *labelframe;
		LabelWidget *labelwidget;
		QPushButton *applyLabels;

		QWidget* createNodeInfoTab();
		QWidget* createLabelTab();
	
};

#endif // NODEPROPERTYWIDGET_H

