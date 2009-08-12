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

	private slots:
		void saveContent();

	protected:
		TextEdit(QWidget *parent = 0);
	
	private:
		static TextEdit *textedit;
		QsciScintilla *editor;
		TextNodeContent *content;

	QToolBar *toolbar;
	QAction *saveAction;
};

#endif // TEXTEDIT_H

