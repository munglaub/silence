#include <QMenu>
#include "gui/filemenu.h"

FileMenu::FileMenu(QWidget *parent)
	: QMenu(parent)
{
	setTitle(tr("&File"));
	addAction(tr("Save"));
	addAction(tr("&Exit"));
}

FileMenu::~FileMenu()
{
}

