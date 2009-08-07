#include "textedit.h"
#include <Qsci/qscilexercpp.h>

TextEdit* TextEdit::textedit = 0;

TextEdit::TextEdit()
{
	// temporarily with a c++ lexer
	setLexer(new QsciLexerCPP());
	// show linenumbers
	setMarginWidth(0, 35);
	setMarginLineNumbers(0, true);
}

TextEdit* TextEdit::create()
{
	if (textedit == 0)
		textedit = new TextEdit;
	return textedit;
}

TextEdit::~TextEdit()
{
}


