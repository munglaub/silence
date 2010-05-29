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

#include "src/commandline/cmdlineoptions.h"

CmdLineOptions::CmdLineOptions()
{
	add("i <id>", ki18n("show node with given id"));
	add("s", ki18n("find nodes"));
	add("text <text>", ki18n("find nodes with a caption that contains text"));
	add("fulltext", ki18n("activate fulltextsearch"));
	add("created <from:to>", ki18n("activate boundaries for the creation date (YYYY-MM-DD:YYYY-MM-DD)"));
	add("modified <from:to>", ki18n("activate boundaries for the modification date (YYYY-MM-DD:YYYY-MM-DD)"));
	add("label <labels>", ki18n("activate filter by labels, node must contain the given labels (label1,label2)"));
	add("banlabel <banlabels>", ki18n("activate filter by labels, node must not contain the given labels (label1,label2)"));
	add("type <type>", ki18n("activate filter by type"));
}


