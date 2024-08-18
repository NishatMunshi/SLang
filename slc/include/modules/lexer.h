#ifndef SLC_MODULES_LEXER_H
#define SLC_MODULES_LEXER_H

#include "ds/string/string_view.h"
#include "ds/list/list.h"

list *lexer_lex(string_view *source_code);

#endif // SLC_MODULES_LEXER_H
