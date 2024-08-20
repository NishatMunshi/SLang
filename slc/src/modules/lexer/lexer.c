#include "modules/lexer/lexer.h"

#include <ctype.h>
#include <stdio.h>

#include "ds/list/list.h"
#include "ds/token/token.h"
#include "memory/arena_allocator.h"
#include "modules/lexer/tokens/num.h"
#include "modules/lexer/tokens/operator.h"
#include "modules/lexer/tokens/unidentified.h"
#include "modules/lexer/tokens/word.h"

struct lexer_struct {
    string_view *source_code;
    size_t current_index;
    size_t line;
    size_t col;
};

static lexer *lexer_create(string_view *source_code) {
    lexer *lexer = arena_allocator_allocate(sizeof(struct lexer_struct));
    lexer->source_code = source_code;
    lexer->current_index = 0;
    lexer->line = 1;
    lexer->col = 1;

    return lexer;
}

size_t lexer_get_current_index(lexer *lexer) {
    return lexer->current_index;
}

size_t lexer_get_current_line(lexer *lexer) {
    return lexer->line;
}

size_t lexer_get_current_col(lexer *lexer) {
    return lexer->col;
}

string_view *lexer_get_source_code(lexer *lexer) {
    return lexer->source_code;
}

static bool lexer_index_in_bound(lexer *lexer) {
    return string_view_in_bound(lexer->source_code, lexer->current_index);
}

char lexer_get_current_char(lexer *lexer) {
    return lexer_index_in_bound(lexer) ? string_view_at(lexer->source_code, lexer->current_index) : '\0';
}

void lexer_advance(lexer *lexer) {
    if (lexer_get_current_char(lexer) == '\n') {
        lexer->line++;
        lexer->col = 0;
    }
    lexer->current_index++;
    lexer->col++;
}

static void lexer_chop_whitespace(lexer *lexer) {
    while (isspace(lexer_get_current_char(lexer))) {
        lexer_advance(lexer);
    }
}

static token *lexer_next_token(lexer *lexer) {
    lexer_chop_whitespace(lexer);

    if (!lexer_index_in_bound(lexer)) {
        return token_create(TOKEN_EOF, string_view_create_from_cstr("EOF"), lexer->line, lexer->col);
    }

    char c = lexer_get_current_char(lexer);
    if (isalpha(c)) {
        return lexer_lex_word(lexer);
    } else if (isdigit(c)) {
        return lexer_lex_num(lexer);
    } else if (ispunct(c)) {
        return lexer_lex_operator(lexer);
    } else {
        return lexer_lex_unidentified_char(lexer);
    }
}

list *lexer_lex(string_view *source_code) {
    lexer *lexer = lexer_create(source_code);
    list *token_list = list_create();

    token *token = NULL;
    do {
        token = lexer_next_token(lexer);
        list_push(token_list, token);
    } while (token_get_type(token) != TOKEN_EOF);

    return token_list;
}
