#ifndef RICHTEXTEDIT_H
#define RICHTEXTEDIT_H

#include "node/richtextnodecontent.h"
#include <QWidget>
#include <QToolBar>
#include <QTextEdit>
#include <QAction>
#include <QComboBox>
#include <QFontComboBox>


class RichTextEdit : public QWidget
{
	Q_OBJECT

	public:
		~RichTextEdit();
		static RichTextEdit* create();
		void setContent(RichTextNodeContent *content);

	protected:
		RichTextEdit(QWidget *parent = 0);

	private slots:
		void saveContent();
		void textBold();
		void textItalic();
		void textUnderline();
		void textAlign(QAction *action);
		void cursorPositionChanged();
		void textColor();
		void textStyle(int styleIndex);
		void textFamily(const QString &font);
		void textSize(const QString &p);
		void currentCharFormatChanged(const QTextCharFormat &format);

	private:
		static RichTextEdit *richtextedit;
		RichTextNodeContent *content;

		// bad naming
		QToolBar *toolbar;
		QToolBar *fontToolbar;
		QTextEdit *textedit;


		QAction *actionSave,
				*actionUndo,
				*actionRedo,
				*actionCut,
				*actionCopy,
				*actionPaste,
				*actionTextBold,
				*actionTextItalic,
				*actionTextUnderline,
				*actionAlignLeft,
				*actionAlignCenter,
				*actionAlignRight,
				*actionAlignJustify,
				*actionTextColor;

		QComboBox *comboStyle;
		QFontComboBox *comboFont;
		QComboBox *comboSize;

		void setupActions();
		void setupFontActions();

		void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
		void alignmentChanged(Qt::Alignment alignment);
		void colorChanged(const QColor &color);
		void fontChanged(const QFont &font);
};

#endif // RICHTEXTEDIT_H

