#include "textedit.h"
#include <Qsci/qscilexercpp.h>

TextEdit::TextEdit()
{
	// temporarily with a c++ lexer
	setLexer(new QsciLexerCPP());
}

TextEdit::~TextEdit()
{
}


