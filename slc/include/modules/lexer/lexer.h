#ifndef SLC_MODULES_LEXER_LEXER_H
#define SLC_MODULES_LEXER_LEXER_H

#include "ds/string/string_view.h"
#include "ds/list/list.h"

typedef struct lexer_struct lexer;

list *lexer_lex(string_view *source_code);

void lexer_advance(lexer *lexer);

char lexer_get_current_char(lexer *lexer);
size_t lexer_get_current_index(lexer *lexer);
size_t lexer_get_current_line(lexer *lexer);
size_t lexer_get_current_col(lexer *lexer);
string_view *lexer_get_source_code(lexer *lexer);


#endif // SLC_MODULES_LEXER_LEXER_H
