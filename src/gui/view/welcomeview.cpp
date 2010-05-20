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

#include <KIcon>
#include <klocalizedstring.h>
#include "src/constants.h"
#include "src/controller.h"
#include "src/gui/view/welcomeview.h"


WelcomeView::WelcomeView()
{
	layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	int row = 0;

	icon = new QLabel;
	icon->setPixmap(KIcon("silence").pixmap(96, 96));
	layout->addWidget(icon, row, 0, 1, 2, Qt::AlignLeft);

	welcome = new QLabel("<font size=\"4\">" + i18n("Welcome to Silence, an information management tool.") + "</font>");
	layout->addWidget(welcome, row, 1, 1, 2, Qt::AlignLeft);
	++row;

	QString html =
		"<font size=\"4\">"
		"<p><table width=400>"
		"<tr><td><b>%1</b></td><td>%2</td></tr>"
		"<tr><td><b>%3</b></td><td>%4</td></tr>"
		"<tr><td><b>%5</b></td><td>%6</td></tr>"
		"</table></p>"
		"</font>"
		;
	html = html
		.arg(i18n("Version"))
		.arg(VERSION)
		.arg(i18n("Authors"))
		.arg(i18n("Manuel Unglaub, Yves Adler, Marcel Winkel"))
		.arg(i18n("License"))
		.arg(i18n("GPLv2"));
	header = new QLabel(html);
	layout->addWidget(header, row, 0, 1, 2);
	++row;

	modifiedCap = new QLabel("<br><h3>" + i18n("Recently modified Nodes") + "</h3>");
	layout->addWidget(modifiedCap, row, 0, 1, 2);
	++row;
	modifiedVal = new QLabel();
	layout->addWidget(modifiedVal, row, 0, 1, 2);
	connect(modifiedVal, SIGNAL(linkActivated(const QString&)), this, SLOT(selectNode(const QString&)));

	setLayout(layout);
}

WelcomeView::~WelcomeView()
{
	delete modifiedVal;
	delete modifiedCap;
	delete header;
	delete welcome;
	delete icon;
	delete layout;
}

bool WelcomeView::hasChanged()
{
	return false;
}

AbstractContentChange* WelcomeView::getChange()
{
	return 0;
}

void WelcomeView::setVisible(bool visible)
{
	if (visible)
		createRecentModifiedList();
	this->AbstractContentView::setVisible(visible);
}

void WelcomeView::selectNode(const QString &link)
{
	Controller::create()->getTreeView()->selectItem(NodeId(link.toInt()));
}

void WelcomeView::createRecentModifiedList()
{
	QString html = "<font size=\"4\">";
	QList<Node*> nodes = Controller::create()->getDataStore()->getRootNode()->toNodeList();
	QList<Node*> recent;
	for (int i = 1; i < nodes.size(); ++i)
	{
		int j=0;
		while(j<recent.size() && nodes.at(i)->getModificationDate() < recent.at(j)->getModificationDate())
			++j;
		recent.insert(j, nodes.at(i));
	}

	for (int i = 0; i < recent.size() && i < 10; ++i){
		html += recent.at(i)->getModificationDate().toString(Qt::SystemLocaleShortDate);
		html += " - <a href=\" ";
		html += *recent.at(i)->getId().toString() + "\" >";
		html += recent.at(i)->getCaption() + "</a><br/>";
	}
	html += "</font>";
	modifiedVal->setText(html);
}


