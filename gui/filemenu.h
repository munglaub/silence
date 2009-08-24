#ifndef FILEMENU_H
#define FILEMENU_H

#include "controller.h"
#include <QMenu>


class FileMenu : public QMenu
{
	public:
		FileMenu(QWidget *parent = 0);
		~FileMenu();

	private:
		Controller *controller;
};

#endif // FILEMENU_H



