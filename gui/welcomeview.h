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

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class WelcomeView : public QWidget
{
	public:
		WelcomeView(QWidget *parent = 0);
		~WelcomeView();

	private:
		QGridLayout *layout;
		QLabel	*icon,
				*welcome,
				*versionCap,
				*versionVal,
				*authorCap,
				*authorVal,
				*licenseCap,
				*licenseVal;
};

#endif // WELCOMEVIEW_H

