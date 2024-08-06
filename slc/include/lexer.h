#ifndef SLC_LEXER_H
#define SLC_LEXER_H

#include "string_view.h"
#include "list.h"

list *lexer_lex(string_view *source_code);

#endif // SLC_LEXER_H
