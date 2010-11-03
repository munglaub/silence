/*
 * Silence
 *
 * Copyright (C) 2009, 2010 Manuel Unglaub <m.unglaub@gmail.com>
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
#include "src/controller.h"
#include "src/gui/sidebar/navigationsidebar.h"
#include "src/controller.h"


NavigationSidebar::NavigationSidebar(const QString &title, QWidget *parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	setObjectName("NavigationBar");
	skip = false;

	KActionCollection *actionCollection = Controller::create()->getActionCollection();

	toolbar = new QToolBar;
	prevAction = actionCollection->addAction("go-previous");
	prevAction->setText(i18nc("go to the previous selected node", "Back"));
	prevAction->setIcon(KIcon("go-previous"));
	prevAction->setShortcut(QKeySequence::Back);
	toolbar->addAction(prevAction);
	connect(prevAction, SIGNAL(triggered()), this, SLOT(previous()));

	nextAction = actionCollection->addAction("go-next");
	nextAction->setText(i18nc("go to the next node", "Forward"));
	nextAction->setIcon(KIcon("go-next"));
	nextAction->setShortcut(QKeySequence::Forward);
	toolbar->addAction(nextAction);
	connect(nextAction, SIGNAL(triggered()), this, SLOT(next()));

	toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	setWidget(toolbar);
	updateActions();

	connect(Controller::create()->getTreeView(), SIGNAL(nodeSelected(Node*)), this, SLOT(selectionChanged(Node*)));
}

NavigationSidebar::~NavigationSidebar()
{
	delete nextAction;
	delete prevAction;
	delete toolbar;
}

void NavigationSidebar::selectionChanged(Node *node)
{
	if (skip)
		return;
	if (node && node == prevList.last())
		return;
	if (node)
	{
		prevList.append(node);
		if (!nextList.isEmpty())
		{
			if (nextList.last() == node)
				nextList.removeLast();
			else
				nextList.clear();
		}
	}
	updateActions();
}

void NavigationSidebar::previous()
{
	skip = true;
	nextList.append(prevList.takeLast());
	Controller::create()->getTreeView()->selectItem(prevList.last()->getId());
	updateActions();
	skip = false;
}

void NavigationSidebar::next()
{
	skip = true;
	Controller::create()->getTreeView()->selectItem(nextList.last()->getId());
	prevList.append(nextList.takeLast());
	updateActions();
	skip = false;
}

void NavigationSidebar::updateActions()
{
	if (prevList.size() > 1)
		prevAction->setEnabled(true);
	else
		prevAction->setEnabled(false);

	if (nextList.size() > 0)
		nextAction->setEnabled(true);
	else
		nextAction->setEnabled(false);
}


