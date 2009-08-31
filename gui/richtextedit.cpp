#include "controller.h"
#include "gui/richtextedit.h"
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QFontDatabase>
#include <QTextCursor>
#include <QTextList>


RichTextEdit* RichTextEdit::richtextedit = 0;

RichTextEdit::RichTextEdit(QWidget *parent)
	: QWidget(parent)
{
	layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	
	toolbar = new QToolBar;
	setupActions();
	layout->addWidget(toolbar);

	fontToolbar = new QToolBar;
	setupFontActions();
	layout->addWidget(fontToolbar);

	textedit = new QTextEdit;
	textedit->setTabStopWidth(40);
	layout->addWidget(textedit);

	findWidget = new RichTextFind(textedit, this);
	findWidget->hide();
	connect(textedit, SIGNAL(textChanged()), findWidget, SLOT(unhighlighte()));
	layout->addWidget(findWidget);

	setLayout(layout);

	// find
	connect(actionFind, SIGNAL(triggered()), findWidget, SLOT(show()));

	// save
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveContent()));

	// alignment
	alignmentChanged(textedit->alignment());
	connect(textedit, SIGNAL(cursorPositionChanged()), 
			this, SLOT(cursorPositionChanged()));

	// color & font
	connect(textedit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
			this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));
	colorChanged(textedit->textColor());	
	fontChanged(textedit->font());

	// undo & redo
	connect(textedit->document(), SIGNAL(undoAvailable(bool)), 
			actionUndo, SLOT(setEnabled(bool)));
	connect(textedit->document(), SIGNAL(redoAvailable(bool)), 
			actionRedo, SLOT(setEnabled(bool)));
	setWindowModified(textedit->document()->isModified());
	actionUndo->setEnabled(textedit->document()->isUndoAvailable());
	actionRedo->setEnabled(textedit->document()->isRedoAvailable());

	connect(actionUndo, SIGNAL(triggered()), textedit, SLOT(undo()));
	connect(actionRedo, SIGNAL(triggered()), textedit, SLOT(redo()));

	// cut, copy, paste
	actionCut->setEnabled(false);
	actionCopy->setEnabled(false);

	connect(actionCut, SIGNAL(triggered()), textedit, SLOT(cut()));
	connect(actionCopy, SIGNAL(triggered()), textedit, SLOT(copy()));
	connect(actionPaste, SIGNAL(triggered()), textedit, SLOT(paste()));

	connect(textedit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
	connect(textedit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

	connect(QApplication::clipboard(), SIGNAL(dataChanged()), 
			this, SLOT(clipboardDataChanged()));
}


RichTextEdit::~RichTextEdit()
{
	delete actionSave;
	delete actionUndo;
	delete actionRedo;
	delete actionCut;
	delete actionCopy;
	delete actionPaste;
	delete actionTextBold;
	delete actionTextItalic;
	delete actionTextUnderline;
	delete actionAlignLeft;
	delete actionAlignCenter;
	delete actionAlignRight;
	delete actionAlignJustify;
	delete actionTextColor;
	delete actionFind;
	delete findWidget;
	delete toolbar;
	delete comboStyle;
	delete comboFont;
	delete comboSize;
	delete fontToolbar;
	delete textedit;
	delete layout;
}

RichTextEdit* RichTextEdit::create()
{
	if (richtextedit == 0)
		richtextedit = new RichTextEdit;
	return richtextedit;
}

void RichTextEdit::setupActions()
{
	EditMenu *menu = Controller::create()->getEditMenu();
	toolbar->setWindowTitle(tr("Edit Actions"));

	actionSave = toolbar->addAction(QIcon("icons/document-save.png"), tr("Save"));
	actionSave->setShortcut(QKeySequence::Save);
	toolbar->addSeparator();

	actionUndo = toolbar->addAction(QIcon("icons/edit-undo.png"), tr("Undo"));
	menu->addAction(actionUndo);
	actionUndo->setShortcut(QKeySequence::Undo);
	actionRedo = toolbar->addAction(QIcon("icons/edit-redo.png"), tr("Redo"));
	menu->addAction(actionRedo);
	actionRedo->setShortcut(QKeySequence::Redo);
	actionCut = toolbar->addAction(QIcon("icons/edit-cut.png"), tr("Cut"));
	menu->addAction(actionCut);
	actionCut->setShortcut(QKeySequence::Cut);
	actionCopy = toolbar->addAction(QIcon("icons/edit-copy.png"), tr("Copy"));
	menu->addAction(actionCopy);
	actionCopy->setShortcut(QKeySequence::Copy);
	actionPaste = toolbar->addAction(QIcon("icons/edit-paste.png"), tr("Paste"));
	menu->addAction(actionPaste);
	actionPaste->setShortcut(QKeySequence::Paste);
	toolbar->addSeparator();

	actionTextBold = toolbar->addAction(QIcon("icons/format-text-bold.png"), tr("Bold"));
	menu->addAction(actionTextBold);
	actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
	QFont bold;
	bold.setBold(true);
	actionTextBold->setFont(bold);
	connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
	actionTextBold->setCheckable(true);

	actionTextItalic = toolbar->addAction(QIcon("icons/format-text-italic.png"), tr("Italic"));
	menu->addAction(actionTextItalic);
	actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont italic;
	italic.setItalic(true);
	actionTextItalic->setFont(italic);
	connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
	actionTextItalic->setCheckable(true);

	actionTextUnderline = toolbar->addAction(QIcon("icons/format-text-underline.png"), tr("Underline"));
	menu->addAction(actionTextUnderline);
	actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
	QFont underline;
	underline.setUnderline(true);
	actionTextUnderline->setFont(underline);
	connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
	actionTextUnderline->setCheckable(true);	
	
	
	toolbar->addSeparator();

	QActionGroup *grp = new QActionGroup(this);
	connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

	actionAlignLeft = new QAction(QIcon("icons/format-justify-left.png"), tr("&Left"), grp);
	actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
	actionAlignLeft->setCheckable(true);
	actionAlignCenter = new QAction(QIcon("icons/format-justify-center.png"), tr("C&enter"), grp);
	actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
	actionAlignCenter->setCheckable(true);
	actionAlignRight = new QAction(QIcon("icons/format-justify-right.png"), tr("&Right"), grp);
	actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
	actionAlignRight->setCheckable(true);
	actionAlignJustify = new QAction(QIcon("icons/format-justify-fill.png"), tr("&Justify"), grp);
	actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
	actionAlignJustify->setCheckable(true);

	toolbar->addActions(grp->actions());
	menu->addActions(grp->actions());
	toolbar->addSeparator();

	// color
	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	actionTextColor = new QAction(pix, tr("&Color..."), this);
	connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
	toolbar->addAction(actionTextColor);
	menu->addAction(actionTextColor);

	actionFind = toolbar->addAction(QIcon("icons/edit-find.png"), tr("Find"));
	actionFind->setShortcut(QKeySequence::Find);
	menu->addAction(actionFind);
}

void RichTextEdit::setupFontActions()
{
	comboStyle = new QComboBox(fontToolbar);
	fontToolbar->addWidget(comboStyle);

	comboStyle->addItem("Standard");
	comboStyle->addItem("Bullet List (Disc)");
	comboStyle->addItem("Bullet List (Circle)");
	comboStyle->addItem("Bullet List (Square)");
	comboStyle->addItem("Ordered List (Decimal)");
	comboStyle->addItem("Ordered List (Alpha lower)");
	comboStyle->addItem("Ordered List (Alpha upper)");
	connect(comboStyle, SIGNAL(activated(int)),
			this, SLOT(textStyle(int)));

	comboFont = new QFontComboBox(fontToolbar);
	fontToolbar->addWidget(comboFont);
	connect(comboFont, SIGNAL(activated(const QString &)),
		this, SLOT(textFamily(const QString &)));


	comboSize = new QComboBox(fontToolbar);
	comboSize->setObjectName("comboSize");
	fontToolbar->addWidget(comboSize);
	comboSize->setEditable(true);
	
	QFontDatabase db;
	foreach(int size, db.standardSizes())
		comboSize->addItem(QString::number(size));
	
	connect(comboSize, SIGNAL(activated(const QString &)),
			this, SLOT(textSize(const QString &)));
	comboSize->setCurrentIndex(comboSize->findText(QString::number(
		QApplication::font().pointSize())));


}

void RichTextEdit::textBold()
{
	QTextCharFormat fmt;
	fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
	mergeFormatOnWordOrSelection(fmt);
}

void RichTextEdit::textItalic()
{
	QTextCharFormat fmt;
	fmt.setFontItalic(actionTextItalic->isChecked());
	mergeFormatOnWordOrSelection(fmt);
}

void RichTextEdit::textUnderline()
{
	QTextCharFormat fmt;
	fmt.setFontUnderline(actionTextUnderline->isChecked());
	mergeFormatOnWordOrSelection(fmt);
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
}

void RichTextEdit::textColor()
{
	QColor col = QColorDialog::getColor(textedit->textColor(), this);
	if (!col.isValid())
		return;
	QTextCharFormat fmt;
	fmt.setForeground(col);
	mergeFormatOnWordOrSelection(fmt);
	colorChanged(col);
}

void RichTextEdit::colorChanged(const QColor &color)
{
	QPixmap pix(16, 16);
	pix.fill(color);
	actionTextColor->setIcon(pix);
}

void RichTextEdit::textStyle(int styleIndex)
{
	QTextCursor cursor = textedit->textCursor();
	
	if (styleIndex != 0) {
		QTextListFormat::Style style = QTextListFormat::ListDisc;
	
		switch (styleIndex) {
			default:
			case 1:
				style = QTextListFormat::ListDisc;
				break;
			case 2:
				style = QTextListFormat::ListCircle;
				break;
			case 3:
				style = QTextListFormat::ListSquare;
				break;
			case 4:
				style = QTextListFormat::ListDecimal;
				break;
			case 5:
				style = QTextListFormat::ListLowerAlpha;
				break;
			case 6:
				style = QTextListFormat::ListUpperAlpha;
				break;
		}
	
		cursor.beginEditBlock();
	
		QTextBlockFormat blockFmt = cursor.blockFormat();
	
		QTextListFormat listFmt;
	
		if (cursor.currentList()) {
			listFmt = cursor.currentList()->format();
		} else {
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}
	
		listFmt.setStyle(style);
	
		cursor.createList(listFmt);
	
		cursor.endEditBlock();
	} else {
		QTextBlockFormat bfmt;
		bfmt.setObjectIndex(-1);
		cursor.mergeBlockFormat(bfmt);
	}
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
	colorChanged(format.foreground().color());
}

void RichTextEdit::setContent(RichTextNodeContent *content)
{
	this->content = content;
	textedit->setHtml(content->getText());
}

void RichTextEdit::saveContent()
{
	content->setText(textedit->toHtml());
}

void RichTextEdit::clipboardDataChanged()
{
	actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

void RichTextEdit::setVisible(bool visible)
{
	this->QWidget::setVisible(visible);
	actionUndo->setVisible(visible);
	actionRedo->setVisible(visible);
	actionCut->setVisible(visible);
	actionCopy->setVisible(visible);
	actionPaste->setVisible(visible);
	actionTextBold->setVisible(visible);
	actionTextItalic->setVisible(visible);
	actionTextUnderline->setVisible(visible);
	actionAlignLeft->setVisible(visible);
	actionAlignCenter->setVisible(visible);
	actionAlignRight->setVisible(visible);
	actionAlignJustify->setVisible(visible);
	actionTextColor->setVisible(visible);
	actionFind->setVisible(visible);
}


