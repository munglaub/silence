#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "node/textnodecontent.h"
#include <QAction>
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

	protected:
		TextEdit(QWidget *parent = 0);
	
	private:
		static TextEdit *textedit;
		QsciScintilla *editor;
		TextNodeContent *content;

		QToolBar *toolbar;
		QAction *actionSave,
				*actionUndo,
				*actionRedo,
				*actionCut,
				*actionCopy,
				*actionPaste;
		

		void setupActions();
		void setupEditor();
};

#endif // TEXTEDIT_H

