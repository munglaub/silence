#include "gui/statusbar.h"
#include <QStatusBar>
#include <QLabel>

StatusBar::StatusBar(QWidget *parent)
	: QStatusBar(parent)
{
	addWidget(new QLabel(tr("0:0")));
	addWidget(new QLabel(tr("changed")));
	addWidget(new QLabel(tr("FancyNode")));
}

StatusBar::~StatusBar()
{
}

