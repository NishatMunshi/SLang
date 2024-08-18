#include "modules/parser/ast_nodes/var.h"

ast_node_var *parser_parse_var(parser *parser) {
    token *token_variable_name = parser_seek_token(parser, TOKEN_IDENT);
    return ast_node_var_create(token_variable_name);
}