#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <Qsci/qsciscintilla.h>

class TextEdit : public QsciScintilla
{
	public:
		TextEdit();
		~TextEdit();
};

#endif // TEXTEDIT_H

