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

#include "src/gui/menu/silencemenu.h"
#include <kaction.h>
#include <klocalizedstring.h>
#include "src/controller.h"


SilenceMenu::SilenceMenu(KActionCollection *actionCollection)
{
	// TODO: implement
	KAction *action = actionCollection->addAction("import_silencexml");
	action->setText(i18n("Import Silence XML-File"));
	connect(action, SIGNAL(triggered()), this, SLOT(importSilenceXml()));

	action = actionCollection->addAction("export_silencexml");
	action->setText(i18n("Export Silence XML-File"));
	connect(action, SIGNAL(triggered()), this, SLOT(showExportSilenceXmlDialog()));


}

SilenceMenu::~SilenceMenu()
{
	// TODO: implement
}

#include<iostream>
void SilenceMenu::showExportSilenceXmlDialog(){
std::cout << "foo" << std::endl;
	ExportSilenceXmlDialog *dlg = new ExportSilenceXmlDialog;
	Controller::create()->getMainWindow()->showDialog(dlg);
	connect(dlg, SIGNAL(exit(ExportSilenceXmlDialog*)), this, SLOT(closeExportSilenceXmlDialog(ExportSilenceXmlDialog*)));
}

void SilenceMenu::closeExportSilenceXmlDialog(ExportSilenceXmlDialog *dlg){
	Controller::create()->getMainWindow()->removeDialog(dlg);
	delete dlg;
}

void SilenceMenu::importSilenceXml(){
std::cout << "bar" << std::endl;
}



