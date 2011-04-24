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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

//#define VERSION "0.1"

static const char VERSION[] = "0.2.1";
static const char APPNAME[] = "Silence";

namespace Actions {
	static const QString SHOW_LABELMANAGEMENT = "showlabelmanagement";
	static const QString SHOW_NODEMANAGEMENT = "shownodemanagement";
	static const QString SHOW_TREENODESIDEBAR = "showtreenodesidebar";
	static const QString SHOW_INFOSIDEBAR = "showinfosidebar";
	static const QString SHOW_NAVISIDEBAR = "shownavisidebar";
	static const QString SHOW_PROPERTYSIDEBAR = "showpropertysidebar";
	static const QString SHOW_SEARCHSIDEBAR = "showsearchsidebar";
	static const QString EXIT = "exit";
	static const QString GO_PREVIOUS = "go-previous";
	static const QString GO_NEXT = "go-next";
	static const QString ADD_NODE = "addnode";
	static const QString ADD_SUBNODE = "addsubnode";
	static const QString REMOVE_NODE = "removenode";
	static const QString SHOW_NODE_PROPERTIES = "shownodeproperties";
	static const QString SHOW_WELCOMEVIEW = "showwelcomeview";


	static const QString SAVE = "si_save";
	static const QString UNDO = "si_undo";
	static const QString REDO = "si_redo";
	static const QString CUT = "si_cut";
	static const QString COPY = "si_copy";
	static const QString PASTE = "si_paste";
	static const QString SELECTALL = "si_selectall";
	static const QString BOLD = "si_bold";
	static const QString ITALIC = "si_italic";
	static const QString UNDERLINE = "si_underline";
	static const QString ALIGN_LEFT = "si_alignleft";
	static const QString ALIGN_RIGHT = "si_alignright";
	static const QString ALIGN_CENTER = "si_aligncenter";
	static const QString ALIGN_JUSTIFY = "si_alignjustify";
	static const QString UNORDERED_LIST = "si_unorderedlist";
	static const QString ORDERED_LIST = "si_orderedlist";
	static const QString INDENT_MORE = "si_indentmore";
	static const QString INDENT_LESS = "si_indentless";
	static const QString INSERT_IMAGE = "si_insertimage";
	static const QString INSERT_RULE = "si_insertrule";
	static const QString INSERT_LINK = "si_insertlink";
	static const QString INSERT_TABLE = "si_inserttable";
	static const QString FIND = "si_find";
	static const QString REPLACE = "si_replace";
	static const QString TEXT_COLOR = "si_textcolor";
	static const QString TEXT_BGCOLOR = "si_textbgcolor";
	static const QString INSERT_TABLE_ROW = "si_inserttablerow";
	static const QString INSERT_TABLE_COLUMN = "si_inserttablecolumn";
	static const QString REMOVE_TABLE_ROW = "si_removetablerow";
	static const QString REMOVE_TABLE_COLUMN = "si_removetablecolumn";
}

#endif // CONSTANTS_H

