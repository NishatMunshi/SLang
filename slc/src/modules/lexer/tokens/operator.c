#include "modules/lexer/tokens/operator.h"

token *lexer_lex_operator(lexer *lexer) {
    char *char_ptr_begin = string_view_get_cstr(lexer_get_source_code(lexer));
    size_t begin = lexer_get_current_index(lexer);
    size_t line = lexer_get_current_line(lexer);
    size_t col = lexer_get_current_col(lexer);
    char c = lexer_get_current_char(lexer);
    lexer_advance(lexer);
    switch (c) {
        case '<':
            c = lexer_get_current_char(lexer);
            lexer_advance(lexer);
            switch (c) {
                case '-':
                    return token_create(TOKEN_LARROW, string_view_create(char_ptr_begin + begin, 2), line, col);
                default:
                    break;
            }
            break;

        case ':':
            c = lexer_get_current_char(lexer);
            lexer_advance(lexer);
            switch (c) {
                case '=':
                    return token_create(TOKEN_DEFN, string_view_create(char_ptr_begin + begin, 2), line, col);
                default:
                    return token_create(TOKEN_COLON, string_view_create(char_ptr_begin + begin, 1), line, col);
            }
            break;

        case '.':
            return token_create(TOKEN_DOT, string_view_create(char_ptr_begin + begin, 1), line, col);
        case '+':
            return token_create(TOKEN_PLUS, string_view_create(char_ptr_begin + begin, 1), line, col);
        case '-':
            return token_create(TOKEN_MINUS, string_view_create(char_ptr_begin + begin, 1), line, col);
        case '(':
            return token_create(TOKEN_LPAREN, string_view_create(char_ptr_begin + begin, 1), line, col);
        case ')':
            return token_create(TOKEN_RPAREN, string_view_create(char_ptr_begin + begin, 1), line, col);
        case '{':
            return token_create(TOKEN_LBRACE, string_view_create(char_ptr_begin + begin, 1), line, col);
        case '}':
            return token_create(TOKEN_RBRACE, string_view_create(char_ptr_begin + begin, 1), line, col);
        case ',':
            return token_create(TOKEN_COMMA, string_view_create(char_ptr_begin + begin, 1), line, col);

        default:
            break;
    }
    return token_create(TOKEN_UNIDENTIFIED, string_view_create(char_ptr_begin + begin, 1), line, col);
}