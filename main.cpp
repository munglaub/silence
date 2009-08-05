#include <QtGui/QApplication>
#include "gui/mainwindow.h"
#include "data/datastore.h"

int main(int argc, char *argv[])
{
	QApplication silence(argc, argv);
	MainWindow w;
	
	//--------
	DataStore *datastore = new DataStore;
	//--------


	w.show();
	return silence.exec();
}



