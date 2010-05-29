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

#include "src/data/node/textcontentchange.h"


TextContentChange::TextContentChange(QString change, TextNodeContent *content, TextEdit *edit)
{
	this->change = change;
	this->content = content;
	this->edit = edit;
}

void TextContentChange::updateContent()
{
	content->setText(change);
}

void TextContentChange::updateContentView()
{
	edit->setText(change);
}


