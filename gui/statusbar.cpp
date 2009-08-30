#include "gui/statusbar.h"


StatusBar::StatusBar(QWidget *parent)
	: QStatusBar(parent)
{
	addWidget(new QLabel(tr("0:0")));
	addWidget(new QLabel(tr("changed")));
	nodeName = new QLabel("");
	addWidget(nodeName);
}

StatusBar::~StatusBar()
{
	delete nodeName;
}

void StatusBar::setNodeName(QString name)
{
	nodeName->setText(name);
}

