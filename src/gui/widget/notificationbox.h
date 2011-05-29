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

#ifndef NOTIFICATIONBOX_H
#define NOTIFICATIONBOX_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "src/data/node/abstractcontentchange.h"
#include "src/data/node/node.h"


/*!\class NotificationBox
 * \brief Inform the user about unsaved nodes.
 *
 * Use this NotificationBox to inform the user about a unsaved node an provide the chance to save the node.
 *
 * \author Manuel Unglaub
 */
class NotificationBox : public QHBoxLayout
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the NotificationBox.
		 * \param node The unsaved node.
		 * \param change The change made to the node.
		 */
		NotificationBox(Node *node, AbstractContentChange *change);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~NotificationBox();

	signals:
		/*!
		 * This signal will be emitted after the user has clicked the save button.
		 * \param node The Node which was saved.
		 * \sa cancelled()
		 */
		void saved(Node *node);

		/*!
		 * This signal will be emitted after the user has clicked the cancel button.
		 * \param node The Node which the user did not want to save.
		 * \sa saved()
		 */
		void cancelled(Node *node);

	private slots:
		void save();
		void cancel();
		void selectNode();
		void checkSelection(Node *node);

	private:
		QHBoxLayout *boxlayout;
		QWidget *box;
		QLabel *info;
		QPushButton *btnSave,
					*btnCancel;
		Node *node;
		AbstractContentChange *change;
		
		void exit();
};

#endif // NOTIFICATIONBOX_H

