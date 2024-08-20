#ifndef SLC_MODULES_PARSER_PARSER_H
#define SLC_MODULES_PARSER_PARSER_H

#include <stdlib.h>

#include "ds/list/list.h"
#include "ds/token/token.h"

typedef struct parser_struct parser;

parser *parser_create(list *token_list);
bool parser_tokens_in_bound(parser *parser);
token *parser_current_token(parser *parser);
token *parser_next_token(parser *parser);
void parser_advance(parser *parser);
void parser_print_error(token *current_token, char *expected_thing);
token *parser_seek_token(parser *parser, token_type type);

#define PARSER_ERROR(CURRENT_TOKEN, EXPECTED_THING_AS_CSTR)    \
    parser_print_error(CURRENT_TOKEN, EXPECTED_THING_AS_CSTR); \
    exit(1);

#endif  // SLC_MODULES_PARSER_PARSER_H