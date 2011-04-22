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
#include "src/controller.h"
#include "src/data/node/rtfcontentchange.h"
#include "src/gui/dialog/newlinkdialog.h"
#include "src/gui/view/richtextedit.h"
#include "src/gui/widget/addimage.h"
#include "src/gui/widget/addtable.h"


RichTextEdit::RichTextEdit(KActionCollection *actionCollection)
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

	setupActions(actionCollection);
	setupFontActions(actionCollection);
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

KAction* RichTextEdit::addAction(KActionCollection *actionCollection, QString name, QString text, QIcon icon)
{
	KAction *action = actionCollection->addAction(name);
	action->setText(text);
	action->setIcon(icon);
	return action;
}

#include "src/constants.h"
#include<iostream>
void RichTextEdit::setupActions(KActionCollection *actionCollection)
{
	//TODO: get actions from actionmanager
	ActionManager *ac = Controller::create()->getActionManager();
//TODO: remove
//isActive = true;
	toolbar->setWindowTitle(i18n("Edit Actions"));

//	actionSave = actionCollection->addAction(KStandardAction::Save, "rtf_save");
actionSave = ac->getAction(Actions::SAVE);
	toolbar->addAction(actionSave);
	actions.append(actionSave);
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveContent()));

	toolbar->addSeparator();

	//actionUndo = actionCollection->addAction(KStandardAction::Undo, "rtf_undo");
	actionUndo = ac->getAction(Actions::UNDO);
	toolbar->addAction(actionUndo);
	actions.append(actionUndo);
	//TODO: das darf nur wenn isActive
	connect(textedit->document(), SIGNAL(undoAvailable(bool)), actionUndo, SLOT(setEnabled(bool)));
	actionUndo->setEnabled(textedit->document()->isUndoAvailable());
	connect(actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
	//connect(actionUndo, SIGNAL(triggered()), textedit, SLOT(undo()));

	//actionRedo = actionCollection->addAction(KStandardAction::Redo, "rtf_redo");
	actionRedo = ac->getAction(Actions::REDO);
	toolbar->addAction(actionRedo);
	actions.append(actionRedo);
	//TODO: das darf nur wenn isActive
	connect(textedit->document(), SIGNAL(redoAvailable(bool)), actionRedo, SLOT(setEnabled(bool)));
	actionRedo->setEnabled(textedit->document()->isRedoAvailable());
	connect(actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
	//connect(actionRedo, SIGNAL(triggered()), textedit, SLOT(redo()));

//	actionCut = actionCollection->addAction(KStandardAction::Cut, "rtf_cut");
	actionCut = ac->getAction(Actions::CUT);
	toolbar->addAction(actionCut);
	actions.append(actionCut);
	actionCut->setEnabled(false);
	connect(actionCut, SIGNAL(triggered()), this, SLOT(cut()));
	connect(textedit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));

//	actionCopy = actionCollection->addAction(KStandardAction::Copy, "rtf_copy");
	actionCopy = ac->getAction(Actions::COPY);
	toolbar->addAction(actionCopy);
	actions.append(actionCopy);
	actionCopy->setEnabled(false);
	connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
	connect(textedit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

//	actionPaste = actionCollection->addAction(KStandardAction::Paste, "rtf_paste");
	actionPaste = ac->getAction(Actions::PASTE);
	toolbar->addAction(actionPaste);
	actions.append(actionPaste);
	connect(actionPaste, SIGNAL(triggered()),this, SLOT(paste()));

//	actionSelectAll = actionCollection->addAction(KStandardAction::SelectAll, "rtf_selectall");
	actionSelectAll = ac->getAction(Actions::SELECTALL);
	toolbar->addAction(actionSelectAll);
	actions.append(actionSelectAll);
	connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAll()));

	toolbar->addSeparator();

//	actionTextBold = addAction(actionCollection, "rtf_bold", i18nc("toggle selected text to bold", "Bold"), KIcon("format-text-bold"));
	actionTextBold = ac->getAction(Actions::BOLD);
	toolbar->addAction(actionTextBold);
	actions.append(actionTextBold);
//	actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
//	QFont bold;
//	bold.setBold(true);
//	actionTextBold->setFont(bold);
	connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
//	actionTextBold->setCheckable(true);

//	actionTextItalic = addAction(actionCollection, "rtf_italic", i18nc("toggle selected text to italic", "Italic"), KIcon("format-text-italic"));
	actionTextItalic = ac->getAction(Actions::ITALIC);
	toolbar->addAction(actionTextItalic);
	actions.append(actionTextItalic);
//	actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
//	QFont italic;
//	italic.setItalic(true);
//	actionTextItalic->setFont(italic);
	connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
//	actionTextItalic->setCheckable(true);

//	actionTextUnderline = addAction(actionCollection, "rtf_underline", i18nc("underline selected text", "Underline"), KIcon("format-text-underline"));
	actionTextUnderline = ac->getAction(Actions::UNDERLINE);
	toolbar->addAction(actionTextUnderline);
	actions.append(actionTextUnderline);
//	actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
//	QFont underline;
//	underline.setUnderline(true);
//	actionTextUnderline->setFont(underline);
	connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
//	actionTextUnderline->setCheckable(true);

	toolbar->addSeparator();

	QActionGroup *grp = new QActionGroup(this);
	connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

//	actionAlignLeft = addAction(actionCollection, "rtf_alignleft", i18nc("justify text left", "Left"), KIcon("format-justify-left"));
	actionAlignLeft = ac->getAction(Actions::ALIGN_LEFT);
	grp->addAction(actionAlignLeft);
	actions.append(actionAlignLeft);
//	actionAlignLeft->setCheckable(true);

//	actionAlignCenter = addAction(actionCollection, "rtf_aligncenter", i18nc("justify text centered", "Center"), KIcon("format-justify-center"));
	actionAlignCenter = ac->getAction(Actions::ALIGN_CENTER);
	grp->addAction(actionAlignCenter);
	actions.append(actionAlignCenter);
//	actionAlignCenter->setCheckable(true);

//	actionAlignRight = addAction(actionCollection, "rtf_alignright", i18nc("justify text right", "Right"), KIcon("format-justify-right"));
	actionAlignRight = ac->getAction(Actions::ALIGN_RIGHT);
	grp->addAction(actionAlignRight);
	actions.append(actionAlignRight);
//	actionAlignRight->setCheckable(true);

//	actionAlignJustify = addAction(actionCollection, "rtf_alignjustify", i18n("Justify"), KIcon("format-justify-fill"));
	actionAlignJustify = ac->getAction(Actions::ALIGN_JUSTIFY);
	grp->addAction(actionAlignJustify);
	actions.append(actionAlignJustify);
//	actionAlignJustify->setCheckable(true);

	toolbar->addActions(grp->actions());
	toolbar->addSeparator();

//	actionUnorderedList = addAction(actionCollection, "rtf_unorderedlist", i18n("Create Unordered List"), KIcon("format-list-unordered"));
	actionUnorderedList = ac->getAction(Actions::UNORDERED_LIST);
	toolbar->addAction(actionUnorderedList);
	actions.append(actionUnorderedList);
	connect(actionUnorderedList, SIGNAL(triggered()), this, SLOT(createUnorderedList()));

//	actionOrderedList = addAction(actionCollection, "rtf_orderedlist", i18n("Create Ordered List"), KIcon("format-list-ordered"));
	actionOrderedList = ac->getAction(Actions::ORDERED_LIST);
	toolbar->addAction(actionOrderedList);
	actions.append(actionOrderedList);
	connect(actionOrderedList, SIGNAL(triggered()), this, SLOT(createOrderedList()));

//	actionIncreaseIndent = addAction(actionCollection, "rtf_increaseindent", i18n("Indent more"), KIcon("format-indent-more"));
	actionIncreaseIndent = ac->getAction(Actions::INDENT_MORE); //TODO: rename
	toolbar->addAction(actionIncreaseIndent);
	actions.append(actionIncreaseIndent);
	connect(actionIncreaseIndent, SIGNAL(triggered()), this, SLOT(increaseIndent()));

//	actionDecreaseIndent = addAction(actionCollection, "rtf_decreaseindent", i18n("Indent less"), KIcon("format-indent-less"));
	actionDecreaseIndent = ac->getAction(Actions::INDENT_LESS); //TODO: rename
	toolbar->addAction(actionDecreaseIndent);
	actions.append(actionDecreaseIndent);
	connect(actionDecreaseIndent, SIGNAL(triggered()), this, SLOT(decreaseIndent()));

	toolbar->addSeparator();

//	actionInsertLink = addAction(actionCollection, "rtf_insertlink", i18n("Insert Link"), KIcon("insert-link"));
	actionInsertLink = ac->getAction(Actions::INSERT_LINK);
	toolbar->addAction(actionInsertLink);
	actions.append(actionInsertLink);
	connect(actionInsertLink, SIGNAL(triggered()), this, SLOT(insertLink()));

//	actionAddPicture = addAction(actionCollection, "rtf_insertimage", i18n("Insert Image"), KIcon("insert-image"));
	actionAddPicture = ac->getAction(Actions::INSERT_IMAGE); //TODO: rename
	toolbar->addAction(actionAddPicture);
	actions.append(actionAddPicture);
	connect(actionAddPicture, SIGNAL(triggered()), this, SLOT(addPicture()));

//	actionInsertTable = addAction(actionCollection, "rtf_inserttable", i18n("Insert Table"), KIcon("insert-table"));
	actionInsertTable = ac->getAction(Actions::INSERT_TABLE);
	toolbar->addAction(actionInsertTable);
	actions.append(actionInsertTable);
	connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(insertTable()));

//	actionInsertRule = addAction(actionCollection, "rtf_insertrule", i18n("Insert Horizontal Rule"), KIcon("insert-horizontal-rule"));
	actionInsertRule = ac->getAction(Actions::INSERT_RULE);
	toolbar->addAction(actionInsertRule);
	actions.append(actionInsertRule);
	connect(actionInsertRule, SIGNAL(triggered()), this, SLOT(insertRule()));

//	actionFind = addAction(actionCollection, "rtf_find", i18n("&Find"), KIcon("edit-find"));
	actionFind = ac->getAction(Actions::FIND);
	toolbar->addAction(actionFind);
	actions.append(actionFind);
	connect(actionFind, SIGNAL(triggered()), this, SLOT(showFind()));

//	actionFindReplace = addAction(actionCollection, "rtf_replace", i18n("Find/Replace"), KIcon("edit-find-replace"));
	actionFindReplace = ac->getAction(Actions::REPLACE);
	toolbar->addAction(actionFindReplace);
	actions.append(actionFindReplace);
	connect(actionFindReplace, SIGNAL(triggered()), this, SLOT(showReplace()));
}

void RichTextEdit::setupFontActions(KActionCollection *actionCollection)
{
	ActionManager *ac = Controller::create()->getActionManager();

//	actionTextColor = addAction(actionCollection, "rtf_textcolor", i18n("Text Color"), KIcon("format-text-color"));
	actionTextColor = ac->getAction(Actions::TEXT_COLOR);
	fontToolbar->addAction(actionTextColor);
	actions.append(actionTextColor);
	connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));

//	actionTextBgColor = addAction(actionCollection, "rtf_textbgcolor", i18n("Text Highlight"), KIcon("format-fill-color"));
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

//	actionInsertTableRow = addAction(actionCollection, "rtf_inserttablerow", i18n("Insert Table Row"), QIcon(":/icons/actions/insert-table-row.png"));
	actionInsertTableRow = ac->getAction(Actions::INSERT_TABLE_ROW);
	fontToolbar->addAction(actionInsertTableRow);
	actions.append(actionInsertTableRow);
	connect(actionInsertTableRow, SIGNAL(triggered()), this, SLOT(insertTableRow()));

//	actionInsertTableColumn = addAction(actionCollection, "rtf_inserttablecolumn", i18n("Insert Table Column"), QIcon(":/icons/actions/insert-table-column.png"));
	actionInsertTableColumn = ac->getAction(Actions::INSERT_TABLE_COLUMN);
	fontToolbar->addAction(actionInsertTableColumn);
	actions.append(actionInsertTableColumn);
	connect(actionInsertTableColumn, SIGNAL(triggered()), this, SLOT(insertTableColumn()));

//	actionRemoveTableRow = addAction(actionCollection, "rtf_removetablerow", i18n("Remove Table Row"), QIcon(":/icons/actions/remove-table-row.png"));
	actionRemoveTableRow = ac->getAction(Actions::REMOVE_TABLE_ROW);
	fontToolbar->addAction(actionRemoveTableRow);
	actions.append(actionRemoveTableRow);
	connect(actionRemoveTableRow, SIGNAL(triggered()), this, SLOT(removeTableRow()));

//	actionRemoveTableColumn = addAction(actionCollection, "rtf_removetablecolumn", i18n("Remove Table Column"), QIcon(":/icons/actions/remove-table-column.png"));
	actionRemoveTableColumn = ac->getAction(Actions::REMOVE_TABLE_COLUMN);
	fontToolbar->addAction(actionRemoveTableColumn);
	actions.append(actionRemoveTableColumn);
	connect(actionRemoveTableColumn, SIGNAL(triggered()), this, SLOT(removeTableColumn()));
}

void RichTextEdit::textBold()
{
	if (isActive){
		std::cout << "RichTextEdit textBold" << std::endl;
		QTextCharFormat fmt;
		fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::textItalic()
{
	if (isActive){
		std::cout << "RichTextEdit textItalic" << std::endl;
		QTextCharFormat fmt;
		fmt.setFontItalic(actionTextItalic->isChecked());
		mergeFormatOnWordOrSelection(fmt);
	}
}

void RichTextEdit::textUnderline()
{
	if (isActive){
		std::cout << "RichTextEdit textUnderline" << std::endl;
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
	std::cout << "RichTextEdit textAlign" << std::endl;
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
	std::cout << "RichTextEdit::textColor" << std::endl;
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
	std::cout << "RichTextEdit::textBgColor" << std::endl;
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
		std::cout << "RichTextEdid save" << std::endl;
		content->setText(textedit->toHtml());
		Controller::create()->getStatusBar()->setSaveStatus(true);
		isChanged = false;
	}
}

void RichTextEdit::undo(){
	if (isActive){
		std::cout << "RichTextEdit undo" << std::endl;
		textedit->undo();
	}
}

void RichTextEdit::redo(){
	if (isActive){
		std::cout << "RichTextEdit redo" << std::endl;
		textedit->redo();
	}
}

void RichTextEdit::cut(){
	if (isActive){
		std::cout << "RichTextEdit cut" << std::endl;
		textedit->cut();
	}
}

void RichTextEdit::copy(){
	if (isActive){
		std::cout << "RichTextEdit copy" << std::endl;
		textedit->copy();
	}
}

void RichTextEdit::paste(){
	if (isActive){
		std::cout << "RichTextEdit paste" << std::endl;
		textedit->paste();
	}
}

void RichTextEdit::selectAll(){
	if (isActive){
		std::cout << "RichTextEdit selectAll" << std::endl;
		textedit->selectAll();
	}
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
}

void RichTextEdit::showFind(){
	if (isActive){
		std::cout << "RichTextEdit showFind" << std::endl;
		findWidget->show();
	}
}

void RichTextEdit::showReplace(){
	if (isActive){
		std::cout << "RichTextEdit showReplace" << std::endl;
		findWidget->showFull();
	}
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

void RichTextEdit::increaseIndent() //TODO: rename
{
	if (isActive){
		std::cout << "RichTextEdit increaseIndent" << std::endl;
		changeIndent(true);
	}
}

void RichTextEdit::decreaseIndent() //TODO: rename
{
	if (isActive){
		std::cout << "RichTextEdit decreaseIndent" << std::endl;
		changeIndent(false);
	}
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
	if (isActive){
		std::cout << "RichTextEdit createOrderedList" << std::endl;
		createList(QTextListFormat::ListDecimal);
	}
}

void RichTextEdit::createUnorderedList()
{
	if (isActive){
		std::cout << "RichTextEdit createUnorderedList" << std::endl;
		createList(QTextListFormat::ListDisc);
	}
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

void RichTextEdit::addPicture() //TODO: rename
{
	if (isActive){
		std::cout << "RichTextEdit addPicture" << std::endl;
		AddImage *addImage = new AddImage(this);
		layout->insertLayout(2, addImage);
		connect(addImage, SIGNAL(addedImage(const QString&)), this, SLOT(insertHtml(QString)));
		connect(textedit, SIGNAL(textChanged()), addImage, SLOT(exit()));
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
	if (isActive){
		std::cout << "RichTextEdit insertRule" << std::endl;
		insertHtml("<hr />");
	}
}

void RichTextEdit::insertLink()
{
	if (!isActive)
		return;
	std::cout << "RichTextEdit insertLink" << std::endl;
	NewLinkDialog *dlg = new NewLinkDialog(this);
	QTextCursor cursor = textedit->textCursor();
	if (cursor.hasSelection())
		dlg->setLinkText(cursor.selectedText());

	layout->insertLayout(2, dlg);
	connect(dlg, SIGNAL(addedLink(const QString&)), this, SLOT(insertHtml(QString)));
	connect(textedit, SIGNAL(textChanged()), dlg, SLOT(exit()));
}

void RichTextEdit::insertTable()
{
	if (isActive){
		std::cout << "RichTextEdit insertTable" << std::endl;
		AddTable *addTable = new AddTable(this);
		layout->insertLayout(2, addTable);
		connect(addTable, SIGNAL(addedTable(const QString&)), this, SLOT(insertHtml(QString)));
		connect(textedit, SIGNAL(textChanged()), addTable, SLOT(exit()));
	}
}

void RichTextEdit::insertTableRow()
{
	if (isActive){
		std::cout << "RichTextEdit::insertTableRow" << std::endl;
		editTable(true, true);
	}
}

void RichTextEdit::insertTableColumn()
{
	if (isActive){
		std::cout << "RichTextEdit::insertTableColumn" << std::endl;
		editTable(false, true);
	}
}

void RichTextEdit::removeTableRow()
{
	if (isActive){
		std::cout << "RichTextEdit::removeTableRow" << std::endl;
		editTable(true, false);
	}
}

void RichTextEdit::removeTableColumn()
{
	if (isActive){
		std::cout << "RichTextEdit::removeTableColumn" << std::endl;
		editTable(false, false);
	}
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



