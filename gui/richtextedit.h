#ifndef RICHTEXTEDIT_H
#define RICHTEXTEDIT_H

#include "gui/textfind.h"
#include "node/richtextnodecontent.h"
#include <QAction>
#include <QComboBox>
#include <QFontComboBox>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>


class RichTextEdit : public QWidget
{
	Q_OBJECT

	public:
		~RichTextEdit();
		static RichTextEdit* create();
		void setContent(RichTextNodeContent *content);

	public slots:
		void setVisible(bool visible);

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
		void clipboardDataChanged();

		void findNext();
		void findPrev();
		void findFirst();

	private:
		static RichTextEdit *richtextedit;
		RichTextNodeContent *content;
		TextFind *findWidget;

		QVBoxLayout *layout;

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
				*actionTextColor,
				*actionFind;

		QComboBox *comboStyle;
		QFontComboBox *comboFont;
		QComboBox *comboSize;

		void setupActions();
		void setupFontActions();

		void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
		void alignmentChanged(Qt::Alignment alignment);
		void colorChanged(const QColor &color);
		void fontChanged(const QFont &font);
		void find(bool forward);
};

#endif // RICHTEXTEDIT_H

