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

#include <iostream>
#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <QTranslator>
#include "src/commandline/cmdlineoptions.h"
#include "src/commandline/cmdmain.h"
#include "src/data/aboutdata.h"
#include "src/gui/mainwindow.h"


int main(int argc, char *argv[])
{
	AboutData aboutData;
	KCmdLineArgs::init(argc, argv, &aboutData);
	KCmdLineArgs::addCmdLineOptions(CmdLineOptions());

	KApplication silence;

	CmdMain *cmd = new CmdMain(KCmdLineArgs::parsedArgs());
	if (cmd->exec() >= 0)
		exit(0);
	delete cmd;

	QTranslator silenceTranslator;
	silenceTranslator.load("silence_" + QLocale::system().name());
//	silenceTranslator.load("silence_de_DE");
	silence.installTranslator(&silenceTranslator);
//	std::cout << QLocale::system().name().toStdString() << std::endl;

	MainWindow *w = new MainWindow();
	w->show();

	return silence.exec();
}



