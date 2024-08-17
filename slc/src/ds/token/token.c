#include "ds/token/token.h"
#include "memory/arena_allocator.h"
#include "ui/ui.h"
#include "utils/utils.h"
#include "slc/slc.h"

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

char * token_get_type_as_string(token_type type) {
    switch (type) {
    case TOKEN_VAR: return "<TOKEN_VAR>"; break;
    case TOKEN_IDENT: return "<TOKEN_IDENT>"; break;
    case TOKEN_LARROW: return "<TOKEN_LARROW>"; break;
    case TOKEN_NUM: return "<TOKEN_NUM>"; break;
    case TOKEN_DOT: return "<TOKEN_DOT>"; break;
    case TOKEN_PLUS: return "<TOKEN_PLUS>"; break;
    case TOKEN_MINUS: return "<TOKEN_MINUS>"; break;
    case TOKEN_LPAREN: return "<TOKEN_LPAREN>"; break;
    case TOKEN_RPAREN: return "<TOKEN_RPAREN>"; break;
    case TOKEN_LBRACE: return "<TOKEN_LBRACE>"; break;
    case TOKEN_RBRACE: return "<TOKEN_RBRACE>"; break;
    case TOKEN_IF: return "<TOKEN_IF>"; break;
    case TOKEN_LOOP: return "<TOKEN_LOOP>"; break;
    case TOKEN_FUNC: return "<TOKEN_FUNC>"; break;
    case TOKEN_COLON: return "<TOKEN_COLON>"; break;
    case TOKEN_COMMA: return "<TOKEN_COMMA>"; break;
    case TOKEN_DEFN: return "<TOKEN_DEFN>"; break;
    case TOKEN_RET: return "<TOKEN_RET>"; break;
    case TOKEN_UNIDENTIFIED: return "<TOKEN_UNIDENTIFIED>"; break;
    case TOKEN_EOF: return "<TOKEN_EOF>"; break;

    default: UNREACHABLE;
    }
}

void token_print_pos(token *token) {
    printf("%s:%zu:%zu: ",slc_get_source_file_name(), token->line, token->col);
}

void token_print(token *token) {
    printf("%s: \"", token_get_type_as_string(token_get_type(token)));
    string_view_print(token->name);
    printf("\"");
}
