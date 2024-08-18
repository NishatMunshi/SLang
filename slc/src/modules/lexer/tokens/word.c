#include "modules/lexer/tokens/word.h"

#include <ctype.h>

token *lexer_lex_word(lexer *lexer) {
    size_t begin = lexer_get_current_index(lexer);
    size_t length = 0;
    size_t line = lexer_get_current_line(lexer);
    size_t col = lexer_get_current_col(lexer);
    while (isalnum(lexer_get_current_char(lexer)) || lexer_get_current_char(lexer) == '_') {
        lexer_advance(lexer);
        length++;
    }

    return token_create_from_word(string_view_create(string_view_get_cstr(lexer_get_source_code(lexer)) + begin, length), line, col);
}