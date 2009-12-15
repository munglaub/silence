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

#include "gui/view/rtf/rtfedit.h"
#include <QMenu>
#include <QContextMenuEvent>

RtfEdit::RtfEdit(QWidget *parent)
	: QTextEdit(parent)
{
	//TODO: remove if not needed
}

RtfEdit::~RtfEdit()
{
	//TODO: remove if not needed
}

void RtfEdit::addContextActions(QList<QAction*> actions)
{
	this->actions.append(actions);
}

void RtfEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	for (int i = 0; i < actions.size(); ++i)
		menu.addAction(actions.at(i));
		
	menu.exec(event->globalPos());
}




