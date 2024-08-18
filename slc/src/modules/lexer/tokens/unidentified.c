#include "modules/lexer/tokens/unidentified.h"

token *lexer_lex_unidentified_char(lexer *lexer) {
    size_t begin = lexer_get_current_index(lexer);
    size_t line = lexer_get_current_line(lexer);
    size_t col = lexer_get_current_col(lexer);
    lexer_advance(lexer);

    return token_create(TOKEN_UNIDENTIFIED,
                        string_view_create(string_view_get_cstr(lexer_get_source_code(lexer)) + begin, 1),
                        line, col);
}