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

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "data/node/textnodecontent.h"
#include "gui/widget/textfind.h"
#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <Qsci/qsciscintilla.h>


/*!\class TextEdit
 * \brief A widget to show and edit text.
 *
 * This TextEdit is the widget to show and modify the TextNodeContent.
 *
 * \author Manuel Unglaub
 */
class TextEdit : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the TextEdit which is a child of parent.
		 * \param parent The parent of this TextEdit.
		 */
		TextEdit(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~TextEdit();

		/*!
		 * Provide the TextEdit with a content to show and edit.
		 * \param content The content which will be shown by this TextEdit.
		 */
		void setContent(TextNodeContent *content);

		/*!
		 * Indicate the syntax highlighting that should be used.
		 * The following syntax highlighters are available: Bash, Batch, CMake, C++, C#, CSS, D, Diff, HTML, IDL, Java, JavaScript, Lua, Makefile, Perl, POV, Python, Ruby, SQL, TeX, VHDL
		 * \param syntax The syntax highlighting that will be used. If syntax does not match an existing syntax no syntax highlighting will be used. If you do not want to use any syntax highlighting you should assign something like "none".
		 */
		void setSyntax(QString syntax);

	public slots:
		/*!
		 * Indicate the visibility of this widget and its actions.
		 * \param visible If true the TextEdit with its actions will be visible.
		 */
		void setVisible(bool visible);

	private slots:
		void saveContent();
		void textModified();
		void clipboardDataChanged();

		void findNext();
		void findPrev();
		void findFirst();
		void replace();
		void replaceAll();

		void contentChanged();
	
	private:
		QsciScintilla *editor;
		TextNodeContent *content;
		QVBoxLayout *layout;
		TextFind *findWidget;

		QToolBar *toolbar;
		QAction *actionSave,
				*actionUndo,
				*actionRedo,
				*actionCut,
				*actionCopy,
				*actionPaste,
				*actionFind,
				*actionSelectAll;
		

		void setupActions();
		void setupEditor();
		bool find(bool forward);
};

#endif // TEXTEDIT_H

