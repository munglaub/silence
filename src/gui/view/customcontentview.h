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

#ifndef CUSTOMCONTENTVIEW_H
#define CUSTOMCONTENTVIEW_H

#include "src/gui/view/abstractcontentview.h"
#include <QList>
#include "src/data/node/customnodeitem.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "src/gui/widget/customnodeelement.h"


class CustomContentView : public AbstractContentView
{
	Q_OBJECT

	public:
		CustomContentView();
		~CustomContentView();

		void setItems(QList<CustomNodeItem*> items);
		bool hasChanged();
		AbstractContentChange* getChange();

	private slots:
		void save();

	private:
		QList<CustomNodeElement*> elements;
		QVBoxLayout *layout;
		QScrollArea *scrollarea;
		QVBoxLayout *scrolllayout;
		QPushButton *btnSave;

};

#endif // CUSTOMCONTENTVIEW_H

