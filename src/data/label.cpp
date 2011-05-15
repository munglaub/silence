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

#include "src/data/label.h"

int Label::highestid = 0;

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
	this->id = ++highestid;
	this->parent = parent;
	this->text = text;
}

int Label::getIndex() const
{
	if (parent)
		return parent->children.indexOf(const_cast<Label*>(this));
	return 0;
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
	if (index < 0 || index > children.size())
		return false;

	children.insert(index, child);
	child->setParent(this);
	return true;
}

bool Label::addChildren(int position, int count)
{
	bool result = false;
	for (int i = 0; i < count; ++i)
		result = addChild(position, new Label());
	return result;
}

bool Label::removeChildren(int position, int count)
{
	if (position < 0 || position + count > children.size())
		return false;
	for (int row = 0; row < count; ++row)
		delete children.takeAt(position);
	return true;
}

Label* Label::takeChild(int position){
	if (position >= 0 && position < children.size())
		return children.takeAt(position);
	else
		return 0;
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

QStringList Label::toStringList()
{
	QStringList result;
	result << text;
	for (int i = 0; i < children.size(); ++i)
		result << children.at(i)->toStringList();
	return result;
}

bool Label::contains(QString labelText)
{
	if (text == labelText)
		return true;
	else {
		bool result = false;
		for (int i = 0; i < children.size() && !result; ++i)
			result = children.at(i)->contains(labelText);
		return result;
	}
}

bool Label::contains(int id)
{
	if (this->id == id)
		return true;
	else {
		bool result = false;
		for (int i = 0; i < children.size() && !result; ++i)
			result = children.at(i)->contains(id);
		return result;
	}
}


int Label::getId(){
	return id;
}



