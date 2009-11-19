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
#include <QGridLayout>
#include <QLabel>


/*!\class InfoSidebar
 * \brief Sidebar to show informations about a node.
 *
 * This sidebar shows informations about a node. It is allowed at the left and right dockingwidgetarea.
 *
 * It shows, the caption, an icon, the creation and modification date, the labels and all available metainformations of the node.
 *
 * \author Manuel Unglaub
 */
class InfoSidebar : public QDockWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs a InfoSidebar which is a child of parent and has the provided window flags. The InfoSidebar will be placed in the right dock widget area.
		 *
		 * The window title is set to title. This title is used when the InfoSidebar is docked and undocked. It is also used in the context menu provided by MainWindow.
		 * The parameters will be passed to the QDockWidget constructor.
		 * \param title The title of the InfoSidebar.
		 * \param parent The parent of this InfoSidebar.
		 * \param flags The window flags of this InfoSidebar.
		 */
		InfoSidebar(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

		/*! The destructor
		 *
		 * Destroys the object.
		 */
		~InfoSidebar();

		/*!
		 * Provide this InfoSidebar with a node to show information about.
		 * \param data The node wich informations will be displayed.
		 */
		void setData(Node *data);

		/*!
		 * Clear out the informations shown at this InfoSidebar.
		 */
		void clearInfos();

	private slots:
		void updateInfos();

	private:
		Node *node; 
		QGridLayout *layout;
		QFrame *frame;
		QLabel	*caption,
				*id,
				*idValue,
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
};

#endif // INFOSIDEBAR_H

