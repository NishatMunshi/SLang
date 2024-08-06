#include "../include/lexer.h"
#include "../include/arena_allocator.h"
#include "../include/list.h"
#include "../include/token.h"

#include <ctype.h>
#include <stdio.h>

typedef struct lexer_struct {
    string_view *source_code;
    size_t current_index;
    size_t line;
    size_t col;
} lexer;

static lexer *lexer_create(string_view *source_code) {
    lexer *lexer = arena_allocator_allocate(sizeof(struct lexer_struct));
    lexer->source_code = source_code;
    lexer->current_index = 0;
    lexer->line = 1;
    lexer->col = 1;
    return lexer;
}

static bool lexer_index_in_bound(lexer *lexer) {
    return string_view_in_bound(lexer->source_code, lexer->current_index);
}

static char lexer_current_char(lexer *lexer) {
    return lexer_index_in_bound(lexer) ? string_view_at(lexer->source_code, lexer->current_index) : '\0';
}

static void lexer_advance(lexer *lexer) {
    if (lexer_current_char(lexer) == '\n') {
        lexer->line++;
        lexer->col = 0;
    }
    lexer->current_index++;
    lexer->col++;
}

static token *lexer_lex_word(lexer *lexer) {
    size_t begin = lexer->current_index;
    size_t length = 0;
    size_t line = lexer->line;
    size_t col = lexer->col;
    while (isalnum(lexer_current_char(lexer)) || lexer_current_char(lexer) == '_') {
        lexer_advance(lexer);
        length++;
    }

    return token_create_from_word(string_view_create(string_view_get_cstr(lexer->source_code) + begin, length), line, col);
}

static token *lexer_lex_num(lexer *lexer) {
    size_t begin = lexer->current_index;
    size_t length = 0;
    size_t line = lexer->line;
    size_t col = lexer->col;
    while (isdigit(lexer_current_char(lexer))) {
        lexer_advance(lexer);
        length++;
    }

    return token_create(TOKEN_NUM, string_view_create(string_view_get_cstr(lexer->source_code) + begin, length), line, col);
}

static token *lexer_lex_operator(lexer *lexer) {
    char *char_ptr_begin = string_view_get_cstr(lexer->source_code);
    size_t begin = lexer->current_index;
    size_t line = lexer->line;
    size_t col = lexer->col;
    char c = lexer_current_char(lexer);
    lexer_advance(lexer);
    switch (c) {
    case '<':
        c = lexer_current_char(lexer);
        lexer_advance(lexer);
        switch (c) {
        case '-': return token_create(TOKEN_LARROW, string_view_create(char_ptr_begin + begin, 2), line, col);
        default: break;
        }
        break;

    case ':':
        c = lexer_current_char(lexer);
        lexer_advance(lexer);
        switch (c) {
        case '=': return token_create(TOKEN_DEFN, string_view_create(char_ptr_begin + begin, 2), line, col);
        default: return token_create(TOKEN_COLON, string_view_create(char_ptr_begin + begin, 1), line, col);
        }
        break;

    case '.': return token_create(TOKEN_DOT, string_view_create(char_ptr_begin + begin, 1), line, col);
    case '+': return token_create(TOKEN_PLUS, string_view_create(char_ptr_begin + begin, 1), line, col);
    case '-': return token_create(TOKEN_MINUS, string_view_create(char_ptr_begin + begin, 1), line, col);
    case '(': return token_create(TOKEN_LPAREN, string_view_create(char_ptr_begin + begin, 1), line, col);
    case ')': return token_create(TOKEN_RPAREN, string_view_create(char_ptr_begin + begin, 1), line, col);
    case '{': return token_create(TOKEN_LBRACE, string_view_create(char_ptr_begin + begin, 1), line, col);
    case '}': return token_create(TOKEN_RBRACE, string_view_create(char_ptr_begin + begin, 1), line, col);
    case ',': return token_create(TOKEN_COMMA, string_view_create(char_ptr_begin + begin, 1), line, col);

    default: break;
    }
    return token_create(TOKEN_UNIDENTIFIED, string_view_create(char_ptr_begin + begin, 1), line, col);
}

static token *lexer_lex_unidentified_char(lexer *lexer) {
    size_t begin = lexer->current_index;
    size_t line = lexer->line;
    size_t col = lexer->col;
    lexer_advance(lexer);

    return token_create(TOKEN_UNIDENTIFIED,
                        string_view_create(string_view_get_cstr(lexer->source_code) + begin, 1),
                        line, col);
}

static void lexer_chop_whitespace(lexer *lexer) {
    while (isspace(lexer_current_char(lexer))) {
        lexer_advance(lexer);
    }
}

static token *lexer_next_token(lexer *lexer) {
    lexer_chop_whitespace(lexer);

    if (!lexer_index_in_bound(lexer)) {
        return token_create(TOKEN_EOF, string_view_create_from_cstr("EOF"), lexer->line, lexer->col);
    }

    char c = lexer_current_char(lexer);
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
