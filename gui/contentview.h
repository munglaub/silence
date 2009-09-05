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

#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include "node/abstractnodecontent.h"
#include <QVBoxLayout>
#include <QWidget>

class ContentView : public QWidget
{
	public:
		ContentView(QWidget *parent = 0);
		~ContentView();

		void setContent(AbstractNodeContent *content);
	private:
		QVBoxLayout *layout;
		QWidget *widget;
};

#endif // CONTENTVIEW_H


