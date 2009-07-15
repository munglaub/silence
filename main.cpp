#include <QtGui/QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication silence(argc, argv);
	MainWindow w;
	w.show();
	return silence.exec();
}



