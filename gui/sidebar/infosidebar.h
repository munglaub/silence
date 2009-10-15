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

#ifndef INFOSIDEBAR_H
#define INFOSIDEBAR_H

#include "data/node/node.h"
#include <QDockWidget>
#include <QLabel>
#include <QGridLayout>


class InfoSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		InfoSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~InfoSidebar();

		void setData(Node *data);
		void clearInfos();

	private slots:
		void updateInfos();

	private:
		Node *node; 

		QGridLayout *layout;
		QFrame *frame;

		// infos aus der node
		QLabel	*caption,
				*created,
				*createdDate,
				*lastedit,
				*lasteditDate,
				*labels,
				*labelsData,
				*metaInfo,
				*metaInfoData,
				*type,
				*typeName,
				*icon;

		// metainfos aus dem content
};

#endif // INFOSIDEBAR_H

