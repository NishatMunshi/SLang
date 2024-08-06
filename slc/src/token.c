#include "../include/token.h"
#include "../include/arena_allocator.h"
#include "../include/slc.h"

#include <assert.h>
#include <stdio.h>

struct token_struct {
    token_type type;
    string_view *name;
    size_t line;
    size_t col;
};

token *token_create(token_type type, string_view *string_view, size_t line, size_t col) {
    token *token = arena_allocator_allocate(sizeof(struct token_struct));
    token->type = type;
    token->name = string_view;
    token->line = line;
    token->col = col;
    return token;
}

token_type token_get_type(token *token) {
    return token->type;
}

string_view *token_get_name(token *token) {
    return token->name;
}

token *token_create_from_word(string_view *word, size_t line, size_t col) {
    if (string_view_compare_with_ctr(word, "var")) {
        return token_create(TOKEN_VAR, word, line, col);
    } else if (string_view_compare_with_ctr(word, "if")) {
        return token_create(TOKEN_IF, word, line, col);
    } else if (string_view_compare_with_ctr(word, "loop")) {
        return token_create(TOKEN_LOOP, word, line, col);
    } else if (string_view_compare_with_ctr(word, "func")) {
        return token_create(TOKEN_FUNC, word, line, col);
    }else if (string_view_compare_with_ctr(word, "ret")) {
        return token_create(TOKEN_RET, word, line, col);
    } else {
        return token_create(TOKEN_IDENT, word, line, col);
    }
}

void token_type_print(token_type type) {
    switch (type) {
    case TOKEN_VAR: printf("<TOKEN_VAR>"); break;
    case TOKEN_IDENT: printf("<TOKEN_IDENT>"); break;
    case TOKEN_LARROW: printf("<TOKEN_LARROW>"); break;
    case TOKEN_NUM: printf("<TOKEN_NUM>"); break;
    case TOKEN_DOT: printf("<TOKEN_DOT>"); break;
    case TOKEN_PLUS: printf("<TOKEN_PLUS>"); break;
    case TOKEN_MINUS: printf("<TOKEN_MINUS>"); break;
    case TOKEN_LPAREN: printf("<TOKEN_LPAREN>"); break;
    case TOKEN_RPAREN: printf("<TOKEN_RPAREN>"); break;
    case TOKEN_LBRACE: printf("<TOKEN_LBRACE>"); break;
    case TOKEN_RBRACE: printf("<TOKEN_RBRACE>"); break;
    case TOKEN_IF: printf("<TOKEN_IF>"); break;
    case TOKEN_LOOP: printf("<TOKEN_LOOP>"); break;
    case TOKEN_FUNC: printf("<TOKEN_FUNC>"); break;
    case TOKEN_COLON: printf("<TOKEN_COLON>"); break;
    case TOKEN_COMMA: printf("<TOKEN_COMMA>"); break;
    case TOKEN_DEFN: printf("<TOKEN_DEFN>"); break;
    case TOKEN_RET: printf("<TOKEN_RET>"); break;
    case TOKEN_UNIDENTIFIED: printf("<TOKEN_UNIDENTIFIED>"); break;
    case TOKEN_EOF: printf("<TOKEN_EOF>"); break;

    default: assert(false && "unreachable");
    }
}

void token_print_pos(token *token) {
    slc_print_source_file_name();
    printf("%zu:%zu: ", token->line, token->col);
}

void token_print(token *token) {
    token_type_print(token->type);
    printf(": \"");
    string_view_print(token->name);
    printf("\"");
}
