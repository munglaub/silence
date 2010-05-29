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

#include "src/data/aboutdata.h"
#include "src/constants.h"
#include <QImage>

AboutData::AboutData()
	: KAboutData ("silence", 0,
		ki18n(APPNAME), VERSION,
		ki18n("An information management tool."),
		KAboutData::License_GPL_V2,
		ki18n("(c) 2009 - 2010, Silence developers"),
		KLocalizedString(),
		"http://silence.sekalura.net",
		"silence@sekalura.net")
{
	addAuthor(ki18n("Manuel Unglaub"), ki18n("Maintainer"), "m.unglaub@gmail.com");
	addAuthor(ki18n("Yves Adler"), KLocalizedString(), "yves.adler@googlemail.com");
}


