/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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

#ifndef SILENCEMENU_H
#define SILENCEMENU_H

#include <kactioncollection.h>
#include "src/data/node/node.h"
#include "src/gui/dialog/exportimportdialog.h"


/*!\class SilenceMenu
 * \brief Consists of actions to import and export data and to exit the application.
 *
 * This menu creates the actions to import and export data.
 *
 * \author Manuel Unglaub
 */
class SilenceMenu : public QObject
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the SilenceMenu and creates actions.
		 * \param actionCollection The applications actioncollection which is needed to add the created actions.
		 */
		SilenceMenu(KActionCollection *actionCollection);

	private slots:
		void showExportImportDialog();
		void closeExportImportDialog(ExportImportDialog *dlg);
		void showImportSilenceXmlDialog();
		void showImportKjotsBookDialog();
		void exportSilenceXml(Node *node, QString fileName);
		void importSilenceXml(Node *node, QString fileName);
		void importKjotsBook(Node *node, QString fileName);
};

#endif // SILENCEMENU_H

