#include "gui/statusbar.h"


StatusBar::StatusBar(QWidget *parent)
	: QStatusBar(parent)
{
	cursorPos = new QLabel("0 : 0");
	addWidget(cursorPos);
	addWidget(new QLabel(tr("changed")));
	nodeName = new QLabel("");
	addWidget(nodeName);
}

StatusBar::~StatusBar()
{
	delete nodeName;
	delete cursorPos;
}

void StatusBar::setNodeName(QString name)
{
	nodeName->setText(name);
}

void StatusBar::setCursorPosition(int line, int col)
{
	QString text = QString::number(line) + " : " + QString::number(col);
	cursorPos->setText(text);
}

