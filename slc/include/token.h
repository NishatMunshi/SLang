#ifndef SLC_TOKEN_H
#define SLC_TOKEN_H

#include "string_view.h"

typedef enum token_type_enum {
    TOKEN_VAR,
    TOKEN_IDENT,
    TOKEN_LARROW,
    TOKEN_NUM,
    TOKEN_DOT,

    TOKEN_PLUS,
    TOKEN_MINUS,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_LBRACE,
    TOKEN_RBRACE,

    TOKEN_IF,
    TOKEN_LOOP,

    TOKEN_FUNC,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_DEFN,

    TOKEN_RET,
    
    TOKEN_UNIDENTIFIED,
    TOKEN_EOF
} token_type;

typedef struct token_struct token;

token *token_create(token_type type, string_view *string_view, size_t line, size_t col);
token *token_create_from_word(string_view *word, size_t line, size_t col);

token_type   token_get_type(token *token);
string_view *token_get_name(token *token);

void token_type_print(token_type type);
void token_print(token *token);
void token_print_pos(token *token);

#endif // SLC_TOKEN_H