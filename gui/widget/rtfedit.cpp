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

#include "controller.h"
#include "data/node/nodeid.h"
#include "gui/widget/rtfedit.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QUrl>


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

bool RtfEdit::canInsertFromMimeData(const QMimeData *source) const
{
	if (source->formats().contains("application/silence-nodeid"))
		return true;
	else
		return QTextEdit::canInsertFromMimeData(source);
}

void RtfEdit::insertFromMimeData(const QMimeData *source)
{
	if (source->formats().contains("application/silence-nodeid"))
	{
		int id = source->data("application/silence-nodeid").toInt();
		Node* node = Controller::create()->getDataStore()->getNode(NodeId(id));
		QUrl url("silence://0.0.0.0/" + QString::number(id));
		if (node && url.isValid())
		{
			QString html = QString("<a href='%1'>%2</a>")
							.arg(url.toString())
							.arg(node->getCaption());
			insertHtml(html);
		}
	} else {
		QTextEdit::insertFromMimeData(source);
	}
}

void RtfEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	for (int i = 0; i < actions.size(); ++i)
		menu.addAction(actions.at(i));
		
	menu.exec(event->globalPos());
}

void RtfEdit::mouseReleaseEvent(QMouseEvent *event)
{
	if (!anchorAt(event->pos()).isEmpty())
	{
		QUrl anchor(anchorAt(event->pos()));
		if (anchor.scheme() == "silence")
		{
			int id = anchor.path().mid(1).toInt();
			Controller::create()->getTreeView()->selectItem(NodeId(id));
		}
	}
	QTextEdit::mouseReleaseEvent(event);
}



