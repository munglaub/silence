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

#ifndef LABELLIST_H
#define LABELLIST_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QAction>


/*!\class LabelList
 * \brief A widget for the SearchNodeSidebar.
 *
 * This widget provides a gui for the SearchNodeSidebar to restrict the search with help of the labels. It consists of a row with a caption and a button to extend it and show its full functionallity.
 * It is possible to add labels which the nodes must have and labels which the nodes must not have (banned labels).
 *
 * \author Manuel Unglaub
 */
class LabelList : public QFrame
{
	Q_OBJECT

	public:
		/*!
		 * The constructor.
		 *
		 * Constructs a LabelList which is a child of parent and has the provided window flags.
		 *
		 * \param parent The parent of this LabelList.
		 * \param f The window flags of this LabelList.
		 */
		explicit LabelList(QWidget *parent = 0, Qt::WindowFlags f = 0);

		/*!
		 * The destructor.
		 *
		 * Destroys the object.
		 */
		~LabelList();

	signals:
		/*!
		 * This signal is emitted after a label is added.
		 *
		 * \param label The added label.
		 */
		void addedLabel(QString label);

		/*!
		 * This signal is emitted after a label is removed.
		 *
		 * \param label The removed label.
		 */
		void removedLabel(QString label);

		/*!
		 * This signal is emitted after a banned label is added.
		 *
		 * \param label. The added banned label.
		 */
		void addedBannedLabel(QString label);

		/*!
		 * This signal is emitted after a banned label is removed.
		 *
		 * \param label The removed banned label.
		 */
		void removedBannedLabel(QString label);

		/*!
		 * This signal is emitted after all labels are removed.
		 *
		 * \sa clearBannedLabels()
		 */
		void clearLabels();

		/*!
		 * This signal is emitted after all banned labels are removed.
		 *
		 * \sa clearLabels()
		 */
		void clearBannedLabels();

	public slots:
		/*!
		 * Use this function if the labels have changed. It will recreate the list of labels and all labels and banned labels will removed.
		 */
		void update();

	private slots:
		void toggleVisibility();
		void showContextMenu();
		void addLabel();
		void addBannedLabel();
		void clear();

	private:
		bool showOptions;
		QGridLayout *layout;
		QLabel *title;
		QPushButton *showBtn;
		QListWidget *list;

		QAction *addLabelAction,
				*addBannedLabelAction,
				*clearAction;

		void fillList();
		void setupActions();

};

#endif // LABELLIST_H


