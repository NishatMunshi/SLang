#include "modules/parser/ast_nodes/ret.h"
#include "modules/parser/ast_nodes/expr.h"

ast_node_ret *parser_parse_ret(parser *parser) {
    parser_seek_token(parser, TOKEN_RET);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    parser_seek_token(parser, TOKEN_DOT);
    return ast_node_ret_create(node_expr);
}
