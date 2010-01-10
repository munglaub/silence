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

#include "src/data/aboutdata.h"

AboutData::AboutData()
	: KAboutData ("silence", 0,
		ki18n("Silence"), "version",
		ki18n("A information management tool."),
		KAboutData::License_GPL_V2,
		ki18n("(c) 2009 - 2010, Silence developers"),
		ki18n("some text .."),
		"no hompage jet",
		"bug report email address")
{
	addAuthor(ki18n("Manuel Unglaub"), ki18n("Current maintainer"), "m.unglaub@gmail.com");
	addAuthor(ki18n("Yves Adler"), KLocalizedString(), "yves.adler@googlemail.com");
}


