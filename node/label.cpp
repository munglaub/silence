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

#include "node/label.h"

Label::Label()
{
	init(0, "");
}

Label::Label(QString text)
{
	init(0, text);
}

Label::~Label()
{
	qDeleteAll(children);
}

void Label::init(Label *parent, QString text)
{
	this->parent = parent;
	this->text = text;
}

QString Label::getText()
{
	return text;
}

void Label::setText(QString text)
{
	this->text = text;
}

Label* Label::getParent()
{
	return parent;
}

void Label::setParent(Label *parent)
{
	this->parent = parent;
}

Label* Label::getChild(int index)
{
	if (index >= 0 && index < children.size())
		return children.at(index);
	else
		return 0;
}

bool Label::addChild(int index, Label *child)
{
	if (index <= 0 || index > children.size())
		return false;

	children.insert(index, child);
	child->setParent(this);
	return true;
}

bool Label::addChild(int index)
{
	return addChild(index, new Label());
}

void Label::appendChild(Label *child)
{
	children.append(child);
	child->setParent(this);
}

int Label::childCount()
{
	return children.size();
}


