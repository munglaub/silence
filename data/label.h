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

#ifndef LABEL_H
#define LABEL_H

#include <QList>
#include <QString>
#include <QStringList>

class Label
{
	public:
		Label();
		Label(QString text);
		~Label();

		int getIndex() const;
		QString getText();
		void setText(QString text);
		Label* getParent();
		Label* getChild(int index);
		bool addChild(int index, Label *child);
		bool addChildren(int position, int count);
		bool removeChildren(int position, int count);
		void appendChild(Label *child);
		int childCount();
		QStringList toStringList();
		bool contains(QString labelText);
	
	protected:
		void setParent(Label *parent);

	private:
		QString text;
		Label* parent;
		QList<Label*> children;
		
		void init(Label *parent, QString text);
};

#endif // LABEL_H

