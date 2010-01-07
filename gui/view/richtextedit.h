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

#ifndef RICHTEXTEDIT_H
#define RICHTEXTEDIT_H

#include "data/node/richtextnodecontent.h"
#include "gui/widget/rtfedit.h"
#include "gui/widget/textfind.h"
#include <QAction>
#include <QComboBox>
#include <QFontComboBox>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>


/*!\class RichTextEdit
 * \brief A widget to show and edit rich text.
 *
 * This RichTextEdit is the widget to show and modify the RichTextNodeContent.
 *
 * \author Manuel Unglaub
 */
class RichTextEdit : public QWidget
{
	Q_OBJECT

	public:
		/*! The constructor.
		 *
		 * Constructs the RichTextEdit which is a child of parent.
		 * \param parent The parent of this RichTextEdit.
		 */
		RichTextEdit(QWidget *parent = 0);

		/*! The destructor.
		 *
		 * Destroys the object.
		 */
		~RichTextEdit();

		/*!
		 * Provide the RichTextEdit with a content to show and edit.
		 * \param content The content which will be shown by this RichTextEdit.
		 */
		void setContent(RichTextNodeContent *content);

	public slots:
		/*!
		 * Indicate the visibility of this widget and its actions.
		 * \param visible If true the RichTextEdit with its actions will be visible.
		 */
		void setVisible(bool visible);

	private slots:
		void saveContent();
		void textBold();
		void textItalic();
		void textUnderline();
		void textAlign(QAction *action);
		void cursorPositionChanged();
		void textColor();
		void textBgColor();
		void textFamily(const QString &font);
		void textSize(const QString &p);
		void currentCharFormatChanged(const QTextCharFormat &format);
		void clipboardDataChanged();

		void contentChanged();

		void findNext();
		void findPrev();
		void findFirst();
		void replace();
		void replaceAll();

		void increaseIndent();
		void decreaseIndent();
		void createOrderedList();
		void createUnorderedList();

		void addPicture();
		void insertRule();
		void insertLink();

		void insertTable();
		void insertTableRow();
		void insertTableColumn();
		void removeTableRow();
		void removeTableColumn();

	private:
		RichTextNodeContent *content;
		TextFind *findWidget;

		QVBoxLayout *layout;

		QToolBar *toolbar;
		QToolBar *fontToolbar;
		RtfEdit *textedit;

		QAction *actionSave,
				*actionUndo,
				*actionRedo,
				*actionCut,
				*actionCopy,
				*actionPaste,
				*actionSelectAll,
				*actionTextBold,
				*actionTextItalic,
				*actionTextUnderline,
				*actionAlignLeft,
				*actionAlignCenter,
				*actionAlignRight,
				*actionAlignJustify,
				*actionTextColor,
				*actionTextBgColor,
				*actionFind,
				*actionFindReplace,
				*actionIncreaseIndent,
				*actionDecreaseIndent,
				*actionOrderedList,
				*actionUnorderedList,
				*actionAddPicture,
				*actionInsertRule,
				*actionInsertLink,
				*actionInsertTable,
				*actionInsertTableRow,
				*actionInsertTableColumn,
				*actionRemoveTableRow,
				*actionRemoveTableColumn;

		QFontComboBox *comboFont;
		QComboBox *comboSize;

		void setupActions();
		void setupFontActions();

		void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
		void alignmentChanged(Qt::Alignment alignment);
		void fontChanged(const QFont &font);
		bool find(bool forward);

		void createList(QTextListFormat::Style style);
		void changeIndent(bool increase);
		void editTable(bool row, bool insert);
};

#endif // RICHTEXTEDIT_H

