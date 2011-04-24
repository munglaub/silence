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

#include <kcolordialog.h>
#include <kfiledialog.h>
#include <klocalizedstring.h>
#include <QApplication>
#include <QClipboard>
#include <QFontDatabase>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QTextList>
#include <QTextTable>
#include "src/constants.h"
#include "src/controller.h"
#include "src/data/node/rtfcontentchange.h"
#include "src/gui/dialog/newlinkdialog.h"
#include "src/gui/view/richtextedit.h"
#include "src/gui/widget/addimage.h"
#include "src/gui/widget/addtable.h"


RichTextEdit::RichTextEdit()
{
	isChanged = false;
	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	
	toolbar = new QToolBar;
	layout->addWidget(toolbar);

	fontToolbar = new QToolBar;
	layout->addWidget(fontToolbar);

	textedit = new RtfEdit;
	textedit->setTabStopWidth(40);
	layout->addWidget(textedit);

	findWidget = new TextFind(this);
	findWidget->hide();
	layout->addWidget(findWidget);
	connect(findWidget, SIGNAL(findNext()), this, SLOT(findNext()));
	connect(findWidget, SIGNAL(findPrev()), this, SLOT(findPrev()));
	connect(findWidget, SIGNAL(searchStringChanged(const QString&)), this, SLOT(findFirst()));
	connect(findWidget, SIGNAL(replace()), this, SLOT(replace()));
	connect(findWidget, SIGNAL(replaceAll()), this, SLOT(replaceAll()));

	setLayout(layout);

	setupActions();
	setupFontActions();
	QList<QAction*> contextActions;
	contextActions.append(actionUndo);
	contextActions.append(actionRedo);
	contextActions.append(actionCut);
	contextActions.append(actionCopy);
	contextActions.append(actionPaste);
	contextActions.append(actionSelectAll);
	textedit->addContextActions(contextActions);

	alignmentChanged(textedit->alignment());
	connect(textedit, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	// color & font
	connect(textedit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)), this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));
	fontChanged(textedit->font());

	setWindowModified(textedit->document()->isModified());
	connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
	connect(textedit, SIGNAL(textChanged()), this, SLOT(contentChanged()));
}


RichTextEdit::~RichTextEdit()
{
	delete findWidget;
	delete toolbar;
	delete comboFont;
	delete comboSize;
	delete fontToolbar;
	delete textedit;
	delete layout;
}

KAction* RichTextEdit::addToolbarAction(QString name){
	KAction* action = Controller::create()->getActionManager()->getAction(name);
	toolbar->addAction(action);
	actions.append(action);
	return action;
}

void RichTextEdit::setupActions()
{
	ActionManager *ac = Controller::create()->getActionManager();
	toolbar->setWindowTitle(i18n("Edit Actions"));

	actionSave = ac->getAction(Actions::SAVE);
	toolbar->addAction(actionSave);
	actions.append(actionSave);
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveContent()));

	toolbar->addSeparator();

	actionUndo = addToolbarAction(Actions::UNDO);
	connect(textedit->document(), SIGNAL(undoAvailable(bool)), this, SLOT(enableUndo(bool)));
	actionUndo->setEnabled(textedit->document()->isUndoAvailable());
	connect(actionUndo, SIGNAL(triggered()), this, SLOT(undo()));

	actionRedo = addToolbarAction(Actions::REDO);
	connect(textedit->document(), SIGNAL(redoAvailable(bool)), this, SLOT(enableRedo(bool)));
	actionRedo->setEnabled(textedit->document()->isRedoAvailable());
	connect(actionRedo, SIGNAL(triggered()), this, SLOT(redo()));

	actionCut = addToolbarAction(Actions::CUT);
	actionCut->setEnabled(false);
	connect(actionCut, SIGNAL(triggered()), this, SLOT(cut()));
	connect(textedit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));

	actionCopy = addToolbarAction(Actions::COPY);
	actionCopy->setEnabled(false);
	connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
	connect(textedit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

	actionPaste = addToolbarAction(Actions::PASTE);
	connect(actionPaste, SIGNAL(triggered()),this, SLOT(paste()));

	actionSelectAll = addToolbarAction(Actions::SELECTALL);
	connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAll()));

	toolbar->addSeparator();

	actionTextBold = addToolbarAction(Actions::BOLD);
	connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));

	actionTextItalic = addToolbarAction(Actions::ITALIC);
	connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));

	actionTextUnderline = addToolbarAction(Actions::UNDERLINE);
	connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));

	toolbar->addSeparator();

	QActionGroup *grp = new QActionGroup(this);
	connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

	actionAlignLeft = ac->getAction(Actions::ALIGN_LEFT);
	grp->addAction(actionAlignLeft);
	actions.append(actionAlignLeft);

	actionAlignCenter = ac->getAction(Actions::ALIGN_CENTER);
	grp->addAction(actionAlignCenter);
	actions.append(actionAlignCenter);

	actionAlignRight = ac->getAction(Actions::ALIGN_RIGHT);
	grp->addAction(actionAlignRight);
	actions.append(actionAlignRight);

	actionAlignJustify = ac->getAction(Actions::ALIGN_JUSTIFY);
	grp->addAction(actionAlignJustify);
	actions.append(actionAlignJustify);

	toolbar->addActions(grp->actions());
	toolbar->addSeparator();

	actionUnorderedList = addToolbarAction(Actions::UNORDERED_LIST);
	connect(actionUnorderedList, SIGNAL(triggered()), this, SLOT(createUnorderedList()));

	actionOrderedList = addToolbarAction(Actions::ORDERED_LIST);
	connect(actionOrderedList, SIGNAL(triggered()), this, SLOT(createOrderedList()));

	actionIndentMore = addToolbarAction(Actions::INDENT_MORE);
	connect(actionIndentMore, SIGNAL(triggered()), this, SLOT(indentMore()));

	actionIndentLess = addToolbarAction(Actions::INDENT_LESS);
	connect(actionIndentLess, SIGNAL(triggered()), this, SLOT(indentLess()));

	toolbar->addSeparator();

	actionInsertLink = addToolbarAction(Actions::INSERT_LINK);
	connect(actionInsertLink, SIGNAL(triggered()), this, SLOT(insertLink()));

	actionInsertImage = addToolbarAction(Actions::INSERT_IMAGE);
	connect(actionInsertImage, SIGNAL(triggered()), this, SLOT(insertImage()));

	actionInsertTable = addToolbarAction(Actions::INSERT_TABLE);
	connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(insertTable()));

	actionInsertRule = addToolbarAction(Actions::INSERT_RULE);
	connect(actionInsertRule, SIGNAL(triggered()), this, SLOT(insertRule()));

	actionFind = addToolbarAction(Actions::FIND);
	connect(actionFind, SIGNAL(triggered()), this, SLOT(showFind()));

	actionFindReplace = addToolbarAction(Actions::REPLACE);
	connect(actionFindReplace, SIGNAL(triggered()), this, SLOT(showReplace()));
}

void RichTextEdit::setupFontActions()
{
	ActionManager *ac = Controller::create()->getActionManager();

	actionTextColor = ac->getAction(Actions::TEXT_COLOR);
	fontToolbar->addAction(actionTextColor);
	actions.append(actionTextColor);
	connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));

	actionTextBgColor = ac->getAction(Actions::TEXT_BGCOLOR);
	fontToolbar->addAction(actionTextBgColor);
	actions.append(actionTextBgColor);
	connect(actionTextBgColor, SIGNAL(triggered()), this, SLOT(textBgColor()));

	comboFont = new QFontComboBox(fontToolbar);
	fontToolbar->addWidget(comboFont);
	connect(comboFont, SIGNAL(activated(const QString &)), this, SLOT(textFamily(const QString &)));

	comboSize = new KComboBox(fontToolbar);
	comboSize->setObjectName("comboSize");
	fontToolbar->addWidget(comboSize);
	comboSize->setEditable(true);
	
	QFontDatabase db;
	foreach(int size, db.standardSizes())
		comboSize->addItem(QString::number(size));

	connect(comboSize, SIGNAL(activated(const QString &)), this, SLOT(textSize(const QString &)));
	comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font().pointSize())));

	actionInsertTableRow = ac->getAction(Actions::INSERT_TABLE_ROW);
	fontToolbar->addAction(actionInsertTableRow);
	actions.append(actionInsertTableRow);
	connect(actionInsertTableRow, SIGNAL(triggered()), this, SLOT(insertTableRow()));

	actionInsertTableColumn = ac->getAction(Actions::INSERT_TABLE_COLUMN);
	fontToolbar->addAction(actionInsertTableColumn);
	actions.append(actionInsertTableColumn);
	connect(actionInsertTableColumn, SIGNAL(triggered()), this, SLOT(insertTableColumn()));

	actionRemoveTableRow = ac->getAction(Actions::REMOVE_TABLE_ROW);
	fontToolbar->addAction(actionRemoveTableRow);
	actions.append(actionRemoveTableRow);
	connect(actionRemoveTableRow, SIGNAL(triggered()), this, SLOT(removeTableRow()));

	actionRemoveTableColumn = ac->getAction(Actions::REMOVE_TABLE_COLUMN);
	fontToolbar->addAction(actionRemoveTableColumn);
	actions.append(actionRemoveTableColumn);
	connect(actionRemoveTableColumn, SIGNAL(triggered()), this, SLOT(removeTableColumn()));
}

void RichTextEdit::textBold()
{
	if (isActive){
		QTextCharFormat fmt;
		fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::textItalic()
{
	if (isActive){
		QTextCharFormat fmt;
		fmt.setFontItalic(actionTextItalic->isChecked());
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::textUnderline()
{
	if (isActive){
		QTextCharFormat fmt;
		fmt.setFontUnderline(actionTextUnderline->isChecked());
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = textedit->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	textedit->mergeCurrentCharFormat(format);
}

void RichTextEdit::textAlign(QAction *action)
{
	if (!isActive)
		return;
	if (action == actionAlignLeft)
		textedit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
	else if (action == actionAlignCenter)
		textedit->setAlignment(Qt::AlignHCenter);
	else if (action == actionAlignRight)
		textedit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
	else if (action == actionAlignJustify)
		textedit->setAlignment(Qt::AlignJustify);

}

void RichTextEdit::alignmentChanged(Qt::Alignment alignment)
{
	if (alignment & Qt::AlignLeft) {
		actionAlignLeft->setChecked(true);
	} else if (alignment & Qt::AlignHCenter) {
		actionAlignCenter->setChecked(true);
	} else if (alignment & Qt::AlignRight) {
		actionAlignRight->setChecked(true);
	} else if (alignment & Qt::AlignJustify) {
		actionAlignJustify->setChecked(true);
	}
}

void RichTextEdit::cursorPositionChanged()
{
	alignmentChanged(textedit->alignment());
	int line = textedit->textCursor().block().blockNumber();
	int col = textedit->textCursor().position() - textedit->textCursor().block().position();
	Controller::create()->getStatusBar()->setCursorPosition(line, col);

	bool active = textedit->textCursor().currentTable() ? true : false;
	actionInsertTableRow->setEnabled(active);
	actionInsertTableColumn->setEnabled(active);
	actionRemoveTableRow->setEnabled(active);
	actionRemoveTableColumn->setEnabled(active);
}

void RichTextEdit::textColor()
{
	if (!isActive)
		return;
	QColor col = textedit->textColor();
	KColorDialog::getColor(col, this);
	if (!col.isValid())
		return;
	QTextCharFormat fmt;
	fmt.setForeground(col);
	mergeFormatOnWordOrSelection(fmt);
}

void RichTextEdit::textBgColor()
{
	if (!isActive)
		return;
	QColor col = textedit->textBackgroundColor();
	KColorDialog::getColor(col, this);
	if (!col.isValid())
		return;
	QTextCharFormat fmt;
	fmt.setBackground(col);
	mergeFormatOnWordOrSelection(fmt);
}

void RichTextEdit::textFamily(const QString &font)
{
	QTextCharFormat fmt;
	fmt.setFontFamily(font);
	mergeFormatOnWordOrSelection(fmt);
}

void RichTextEdit::textSize(const QString &p)
{
	qreal pointSize = p.toFloat();
	if (p.toFloat() > 0) {
		QTextCharFormat fmt;
		fmt.setFontPointSize(pointSize);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::fontChanged(const QFont &font)
{
	comboFont->setCurrentIndex(comboFont->findText(QFontInfo(font).family()));
	comboSize->setCurrentIndex(comboSize->findText(QString::number(font.pointSize())));
	actionTextBold->setChecked(font.bold());
	actionTextItalic->setChecked(font.italic());
	actionTextUnderline->setChecked(font.underline());
}

void RichTextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
	fontChanged(format.font());
}

void RichTextEdit::setContent(RichTextNodeContent *content)
{
	this->content = content;
	textedit->setHtml(content->getText());
	Controller::create()->getStatusBar()->setSaveStatus(true);
	isChanged = false;
}

void RichTextEdit::setHtml(QString text)
{
	textedit->setHtml(text);
}

bool RichTextEdit::hasChanged()
{
	return isChanged;
}

AbstractContentChange* RichTextEdit::getChange()
{
	return new RtfContentChange(textedit->toHtml(), content, this);
}

void RichTextEdit::saveContent()
{
	if (isActive){
		content->setText(textedit->toHtml());
		Controller::create()->getStatusBar()->setSaveStatus(true);
		isChanged = false;
	}
}

void RichTextEdit::undo(){
	if (isActive)
		textedit->undo();
}

void RichTextEdit::enableUndo(bool enable){
	if (isActive)
		actionUndo->setEnabled(enable);
}

void RichTextEdit::redo(){
	if (isActive)
		textedit->redo();
}

void RichTextEdit::enableRedo(bool enable){
	if (isActive)
		actionRedo->setEnabled(enable);
}

void RichTextEdit::cut(){
	if (isActive)
		textedit->cut();
}

void RichTextEdit::copy(){
	if (isActive)
		textedit->copy();
}

void RichTextEdit::paste(){
	if (isActive)
		textedit->paste();
}

void RichTextEdit::selectAll(){
	if (isActive)
		textedit->selectAll();
}

void RichTextEdit::clipboardDataChanged()
{
	actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

void RichTextEdit::setVisible(bool visible)
{
	this->isActive = visible;
	this->QWidget::setVisible(visible);
	for (int i = 0; i < actions.size(); ++i)
		actions.at(i)->setVisible(visible);
	actionUndo->setEnabled(textedit->document()->isUndoAvailable());
	actionRedo->setEnabled(textedit->document()->isRedoAvailable());
}

void RichTextEdit::showFind(){
	if (isActive)
		findWidget->show();
}

void RichTextEdit::showReplace(){
	if (isActive)
		findWidget->showFull();
}

bool RichTextEdit::find(bool forward)
{
	bool found = false;
	if (findWidget->getSearchString().isEmpty())
		return found;

	QTextDocument::FindFlags flags = 0;
	
	if (!forward)
		flags = flags | QTextDocument::FindBackward;
	if (findWidget->getCaseSensitivity())
		flags = flags | QTextDocument::FindCaseSensitively;
	if (findWidget->getWholeWord())
		flags = flags | QTextDocument::FindWholeWords;

	found = textedit->find(findWidget->getSearchString(), flags);
	findWidget->setFound(found);
	return found;
}

void RichTextEdit::findNext()
{
	find(true);
}

void RichTextEdit::findPrev()
{
	find(false);
}

void RichTextEdit::findFirst()
{
	textedit->moveCursor(QTextCursor::Start);
	find(true);
}

void RichTextEdit::replace()
{
	if (textedit->textCursor().selectedText() == findWidget->getSearchString())
		textedit->insertPlainText(findWidget->getReplaceString());
	else
		if (find(true))
			textedit->insertPlainText(findWidget->getReplaceString());
}

void RichTextEdit::replaceAll()
{
	textedit->moveCursor(QTextCursor::Start);

	bool found = false;
	do {
		found = find(true);
		if (found)
			textedit->insertPlainText(findWidget->getReplaceString());
	} while (found);
}

void RichTextEdit::indentMore()
{
	if (isActive)
		changeIndent(true);
}

void RichTextEdit::indentLess()
{
	if (isActive)
		changeIndent(false);
}

void RichTextEdit::changeIndent(bool increase)
{
	int indent = increase ? 1 : -1;
	QTextCursor cursor = textedit->textCursor();
	if (cursor.currentList())
	{
		cursor.beginEditBlock();

		QTextListFormat listFmt = cursor.currentList()->format();
		listFmt.setIndent(listFmt.indent() + indent);
		if (listFmt.indent() > 0 || increase)
		{
			switch (listFmt.style()) {
				default:
				case QTextListFormat::ListDisc:
					listFmt.setStyle(increase ? QTextListFormat::ListCircle : QTextListFormat::ListSquare);
					break;
				case QTextListFormat::ListCircle:
					listFmt.setStyle(increase ? QTextListFormat::ListSquare : QTextListFormat::ListDisc);
					break;
				case QTextListFormat::ListSquare:
					listFmt.setStyle(increase ? QTextListFormat::ListDisc : QTextListFormat::ListCircle);
					break;

				case QTextListFormat::ListDecimal:
					listFmt.setStyle(increase ? QTextListFormat::ListLowerAlpha : QTextListFormat::ListUpperAlpha);
					break;
				case QTextListFormat::ListLowerAlpha:
					listFmt.setStyle(increase ? QTextListFormat::ListUpperAlpha : QTextListFormat::ListDecimal);
					break;
				case QTextListFormat::ListUpperAlpha:
					listFmt.setStyle(increase ? QTextListFormat::ListDecimal : QTextListFormat::ListLowerAlpha);
					break;
			}
			cursor.createList(listFmt);
		}
		cursor.endEditBlock();
	} else {
		if (cursor.blockFormat().indent() > 0 || increase)
		{
			QTextBlockFormat bfmt;
			bfmt.setIndent(cursor.blockFormat().indent() + indent);
			cursor.mergeBlockFormat(bfmt);
		}
	}
}

void RichTextEdit::createOrderedList()
{
	if (isActive)
		createList(QTextListFormat::ListDecimal);
}

void RichTextEdit::createUnorderedList()
{
	if (isActive)
		createList(QTextListFormat::ListDisc);
}

void RichTextEdit::createList(QTextListFormat::Style style)
{
	QTextCursor cursor = textedit->textCursor();
	if (cursor.currentList())
		return;

	cursor.beginEditBlock();

	QTextBlockFormat blockFmt = cursor.blockFormat();
	QTextListFormat listFmt;

	listFmt.setIndent(blockFmt.indent() + 1);
	blockFmt.setIndent(0);
	cursor.setBlockFormat(blockFmt);

	listFmt.setStyle(style);
	cursor.createList(listFmt);

	cursor.endEditBlock();
}

void RichTextEdit::contentChanged()
{
	Controller::create()->getStatusBar()->setSaveStatus(false);
	isChanged = true;
}

void RichTextEdit::insertImage()
{
	if (isActive){
		AddImage *addImage = new AddImage(this);
		layout->insertLayout(2, addImage);
		connect(addImage, SIGNAL(addedImage(const QString&)), this, SLOT(insertHtml(QString)));
		connect(textedit, SIGNAL(textChanged()), addImage, SLOT(exit()));
		addImage->setFocus();
	}
}

void RichTextEdit::insertHtml(QString html)
{
	QTextCursor cursor = textedit->textCursor();
	cursor.beginEditBlock();
	cursor.insertHtml(html);
	cursor.endEditBlock();
	textedit->moveCursor(QTextCursor::NextBlock);
}

void RichTextEdit::insertRule()
{
	if (isActive)
		insertHtml("<hr />");
}

void RichTextEdit::insertLink()
{
	if (!isActive)
		return;
	NewLinkDialog *dlg = new NewLinkDialog(this);
	QTextCursor cursor = textedit->textCursor();
	if (cursor.hasSelection())
		dlg->setLinkText(cursor.selectedText());

	layout->insertLayout(2, dlg);
	connect(dlg, SIGNAL(addedLink(const QString&)), this, SLOT(insertHtml(QString)));
	connect(textedit, SIGNAL(textChanged()), dlg, SLOT(exit()));
	dlg->setFocus();
}

void RichTextEdit::insertTable()
{
	if (isActive){
		AddTable *addTable = new AddTable(this);
		layout->insertLayout(2, addTable);
		connect(addTable, SIGNAL(addedTable(const QString&)), this, SLOT(insertHtml(QString)));
		connect(textedit, SIGNAL(textChanged()), addTable, SLOT(exit()));
	}
}

void RichTextEdit::insertTableRow()
{
	if (isActive)
		editTable(true, true);
}

void RichTextEdit::insertTableColumn()
{
	if (isActive)
		editTable(false, true);
}

void RichTextEdit::removeTableRow()
{
	if (isActive)
		editTable(true, false);
}

void RichTextEdit::removeTableColumn()
{
	if (isActive)
		editTable(false, false);
}

void RichTextEdit::editTable(bool row, bool insert)
{
	QTextCursor cursor = textedit->textCursor();
	if (cursor.currentTable())
	{
		cursor.beginEditBlock();

		int number = 1;
		QTextTable *table = cursor.currentTable();
		int index = row ? table->cellAt(cursor).row() : table->cellAt(cursor).column();

		if (row)
			if (insert)
				table->insertRows(index, number);
			else
				table->removeRows(index, number);
		else
			if (insert)
				table->insertColumns(index, number);
			else
				table->removeColumns(index, number);
		cursor.endEditBlock();
	}
}



