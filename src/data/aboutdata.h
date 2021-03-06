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

#ifndef ABOUTDATA_H
#define ABOUTDATA_H

#include <kaboutdata.h>


/*!\class AboutData
 * \brief AboutData of Silence.
 *
 * This AboutData is used to strore information about Silence. It stores information like authors, license and copyright information.
 * Inherits from KAboutData.
 *
 * \author Manuel Unglaub
 */
class AboutData : public KAboutData
{
	public:
		/*!
		 * The constructor.
		 *
		 * Constructs the AboutData.
		 */
		AboutData();

};

#endif // ABOUTDATA_H

