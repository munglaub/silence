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

#include "src/commandline/cmdmain.h"
#include "src/gui/mainwindow.h"
#include <QTranslator>
#include <QtGui/QApplication>
//#include <iostream>


int main(int argc, char *argv[])
{
	QApplication silence(argc, argv);

	QTranslator silenceTranslator;
	silenceTranslator.load("silence_" + QLocale::system().name());
//	silenceTranslator.load("silence_de_DE");
	silence.installTranslator(&silenceTranslator);
//	std::cout << QLocale::system().name().toStdString() << std::endl;

	MainWindow *w;
	CmdMain *cmd;
	if (argc <= 1){
		w = new MainWindow();
		w->show();
	} else {
		cmd = new CmdMain();
		cmd->exec(argc, argv);
		delete cmd;
		return 0; // TODO: do it the right way
	}

	return silence.exec();
}



