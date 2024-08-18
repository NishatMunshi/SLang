#include "modules/parser/ast_nodes/num.h"

ast_node_num *parser_parse_num(parser *parser) {
    token *token_num = parser_seek_token(parser, TOKEN_NUM);
    return ast_node_num_create(token_get_name(token_num));
}