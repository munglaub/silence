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

#include <kaction.h>
#include <klocalizedstring.h>
#include "src/controller.h"
#include "src/gui/menu/silencemenu.h"


SilenceMenu::SilenceMenu(KActionCollection *actionCollection)
{
	KAction *action = actionCollection->addAction("import_silencexml");
	action->setText(i18n("Import Silence XML-File"));
	connect(action, SIGNAL(triggered()), this, SLOT(showImportSilenceXmlDialog()));

	action = actionCollection->addAction("export_silencexml");
	action->setText(i18n("Export Silence XML-File"));
	connect(action, SIGNAL(triggered()), this, SLOT(showExportImportDialog()));
}

void SilenceMenu::showExportImportDialog(){
	ExportImportDialog *dlg = new ExportImportDialog(ExportImportDialog::Export);
	dlg->setCaption(i18n("Export Silence XML-File"));
	dlg->setHint(i18n("Export data in the Silence format."));
	dlg->setOptions(i18n("Export all"), i18n("Export partial"));
	dlg->setPathCaption(i18n("Exportfile"));
	dlg->setButtonCaptions(i18n("Abort"), i18n("Export"));
	dlg->setErrorMessage(i18n("Select a file to export the data."));
	Controller::create()->getMainWindow()->showDialog(dlg);
	connect(dlg, SIGNAL(executed(Node*, QString)), this, SLOT(exportSilenceXml(Node*, QString)));
	connect(dlg, SIGNAL(exit(ExportImportDialog*)), this, SLOT(closeExportImportDialog(ExportImportDialog*)));
}

void SilenceMenu::showImportSilenceXmlDialog(){
	ExportImportDialog *dlg = new ExportImportDialog(ExportImportDialog::Import);
	dlg->setCaption(i18n("Import Silence XML-File"));
	dlg->setHint(i18n("Import data from a file in the Silence format."));
	dlg->setOptions(i18n("Add to toplevel"), i18n("Select parent Node"));
	dlg->setPathCaption(i18n("Importfile"));
	dlg->setButtonCaptions(i18n("Abort"), i18n("Import"));
	dlg->setErrorMessage(i18n("Select a file to import the data from."));

	Controller::create()->getMainWindow()->showDialog(dlg);
	connect(dlg, SIGNAL(executed(Node*, QString)), this, SLOT(importSilenceXml(Node*, QString)));
	connect(dlg, SIGNAL(exit(ExportImportDialog*)), this, SLOT(closeExportImportDialog(ExportImportDialog*)));

}

void SilenceMenu::closeExportImportDialog(ExportImportDialog *dlg){
	Controller::create()->getMainWindow()->removeDialog(dlg);
	delete dlg;
}

void SilenceMenu::exportSilenceXml(Node *node, QString fileName){
	XmlDataStore::writeToXmlFile(fileName, node);
}

void SilenceMenu::importSilenceXml(Node *node, QString fileName){
	XmlDataStore::readFromXmlFile(fileName, node);
}

