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
		~TextEdit();
		static TextEdit* create();
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

	protected:
		TextEdit(QWidget *parent = 0);
	
	private:
		static TextEdit *textedit;
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
		void find(bool forward);
};

#endif // TEXTEDIT_H

