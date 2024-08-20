#include "modules/parser/parser.h"

#include <stdio.h>

#include "memory/arena_allocator.h"

struct parser_struct {
    list *token_list;
    list_node *current_token_list_node;
};

parser *parser_create(list *token_list) {
    parser *parser = arena_allocator_allocate(sizeof(struct parser_struct));
    parser->token_list = token_list;
    parser->current_token_list_node = list_get_begin(token_list);

    return parser;
}

bool parser_tokens_in_bound(parser *parser) {
    return parser->current_token_list_node != list_get_end(parser->token_list);
}

token *parser_current_token(parser *parser) {
    return parser_tokens_in_bound(parser) ? list_node_get_data(parser->current_token_list_node) : NULL;
}

token *parser_next_token(parser *parser) {
    return list_node_get_data(list_node_get_next(parser->current_token_list_node));
}

void parser_advance(parser *parser) {
    parser->current_token_list_node = list_node_get_next(parser->current_token_list_node);
}

void parser_print_error(token *current_token, char *expected_thing) {
    printf("[SLC]: [PARSER ERROR]: ");
    token_print_pos(current_token);
    printf("Expected %s; Instead got: ", expected_thing);
    token_print(current_token);
    printf(" \n");
}

token *parser_seek_token(parser *parser, token_type type) {
    token *current_token = parser_current_token(parser);
    if (!current_token) {
        return NULL;
    }
    if (token_get_type(current_token) != type) {
        PARSER_ERROR(current_token, token_get_type_as_string(type));
    } else {
        parser_advance(parser);
        return current_token;
    }
}