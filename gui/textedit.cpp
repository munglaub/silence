#include "textedit.h"
#include <Qsci/qscilexercpp.h>

TextEdit::TextEdit()
{
	// temporarily with a c++ lexer
	setLexer(new QsciLexerCPP());
	// show linenumbers
	setMarginWidth(0, 35);
	setMarginLineNumbers(0, true);
}

TextEdit::~TextEdit()
{
}


