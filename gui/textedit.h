#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <Qsci/qsciscintilla.h>
#include <QWidget>


class TextEdit : public QWidget
{
	public:
		~TextEdit();
		static TextEdit* create();
		void setText(const QString &text);

	protected:
		TextEdit(QWidget *parent = 0);
	
	private:
		static TextEdit *textedit;
		QsciScintilla *editor;
};

#endif // TEXTEDIT_H

