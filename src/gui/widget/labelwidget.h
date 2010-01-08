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

#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "src/data/label.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QWidget>


/*!\class LabelWidget
 * \brief A widget to select labels.
 *
 * Use this widget to select labels. It contains a slot to preselect labels an a button to show the LabelManagementDialog.
 *
 * \author Manuel Unglaub
 */
class LabelWidget : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the LabelWidget which is a child of parent.
		 * \param parent The parent of this LabelWidget.
		 * \param showManageLabelsBtn Indicates if the button to manage the labels is visible.
		 */
		LabelWidget(QWidget *parent = 0, bool showManageLabelsBtn = true);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~LabelWidget();

	public slots:
		/*!
		 * Get a QStringList with all the selected labels.
		 * \return The selected labels.
		 */
		QStringList getLabels() const;

		/*!
		 * Select all labels which the QStringList contains.
		 * \param select The labels which will be selected.
		 */
		void selectLabels(QStringList select);

		/*!
		 * Open the LabelManagementDialog.
		 */
		void manageLabels();

		/*!
		 * Reload the the tree with the labels to show the modification made in the LabelManagementDialog.
		 */
		void updateLabels();

	private slots:
		void itemActivated(QTreeWidgetItem *item, int column);

	private:
		QGridLayout *layout;
		QTreeWidget *labeltree;
		QPushButton *manageLabelsBtn;

		void setupTree();
		void fillTree();
		void addLabel(QTreeWidgetItem* parent, Label* label);
		void deselectChildren(QTreeWidgetItem* item);
};

#endif // LABELWIDGET_H

