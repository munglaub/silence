/*
 * Silence
 *
 * Copyright (C) 2011 Manuel Unglaub
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
 *
 * You should have received a copy of the GNU General Public License
 * along with Silence.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <krun.h>
#include "src/controller.h"
#include "src/data/node/nodeid.h"
#include "src/gui/view/bookview.h"


BookView::BookView()
{
	layout = new QVBoxLayout;
	view = new QTextBrowser;
	view->setOpenLinks(false);
	layout->addWidget(view);

	setLayout(layout);


	connect(view, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(onClick(const QUrl&)));
}

BookView::~BookView()
{
	// TODO: implement
}

bool BookView::hasChanged()
{
	return false;
}

AbstractContentChange* BookView::getChange()
{
	return 0;
}

void BookView::setHtmlContent(QString html)
{
	view->setHtml(html);
}

void BookView::onClick(const QUrl& url)
{
	if (url.scheme() == "silence"){
		int id = url.path().mid(1).toInt();
		Controller::create()->getTreeView()->selectItem(NodeId(id));
	} else if(url.isRelative()) {
		view->setSource(url);
	} else {
		new KRun(url, this);
	}
}


