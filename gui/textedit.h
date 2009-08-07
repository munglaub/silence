#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <Qsci/qsciscintilla.h>

class TextEdit : public QsciScintilla
{
	public:
		~TextEdit();
		static TextEdit* create();

	protected:
		TextEdit();
	
	private:
		static TextEdit *textedit;
};

#endif // TEXTEDIT_H

