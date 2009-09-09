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

#include "node/textnodecontent.h"
#include <QAction>
#include <QVBoxLayout>
#include "gui/textfind.h"
#include <Qsci/qsciscintilla.h>
#include <QToolBar>
#include <QWidget>


class TextEdit : public QWidget
{
	Q_OBJECT

	public:
		TextEdit(QWidget *parent = 0);
		~TextEdit();
		void setContent(TextNodeContent *content);
		void setSyntax(QString syntax);

	public slots:
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
				*actionFind;
		

		void setupActions();
		void setupEditor();
		bool find(bool forward);
};

#endif // TEXTEDIT_H

