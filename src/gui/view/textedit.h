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

#include <kactioncollection.h>
#include "src/data/node/textnodecontent.h"
#include "src/gui/view/abstractcontentview.h"

namespace KTextEditor
{
	class Document;
	class View;
	class Editor;
	class Cursor;
}

using namespace KStandardAction;

class QAction;
class QActionGroup;
class QToolBar;
class QVBoxLayout;


/*!\class TextEdit
 * \brief A widget to show and edit text.
 *
 * This TextEdit is the widget to show and modify the TextNodeContent. It is supposed to handle plain text and provieds syntax highlighting for different languages.
 *
 * \author Manuel Unglaub
 */
class TextEdit : public AbstractContentView
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the TextEdit.
		 * \param actionCollection The action collection of the application.
		 */
		TextEdit(KActionCollection *actionCollection);

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
		 * Changes the text of the TextEdit.
		 * \param text The new text of the TextEdit.
		 */
		void setText(QString text);

		/*!
		 * Indicate the syntax highlighting that should be used.
		 * \param syntax The syntax highlighting that will be used. If syntax does not match an existing syntax no syntax highlighting will be used. If you do not want to use any syntax highlighting you should assign "None".
		 */
		void setSyntax(QString syntax);

		bool hasChanged();
		AbstractContentChange* getChange();

	public slots:
		/*!
		 * Indicate the visibility of this widget and its actions.
		 * \param visible If true the TextEdit with its actions will be visible.
		 */
		void setVisible(bool visible);

	private slots:
		void saveContent();
		void contentChanged();
		void cursorPositionChanged(KTextEditor::View *view, const KTextEditor::Cursor &newPosition);
	
	private:
		TextNodeContent *content;
		bool isChanged;
		QVBoxLayout *layout;

		QActionGroup *actionGroup;

		QToolBar *toolbar;
		QAction *saveAction;

		KTextEditor::View *view;
		KTextEditor::Document *document;
		KTextEditor::Editor *editor;
		

		void addAction(KActionCollection *actionCollection, KStandardAction::StandardAction actionType, QString name);
		void setupActions(KActionCollection *actionCollection);
		void setupEditor();
};

#endif // TEXTEDIT_H

