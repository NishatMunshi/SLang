#include "modules/parser/loop.h"
#include "modules/parser/expr.h"
#include "modules/parser/scope.h"


ast_node_loop *parser_parse_loop(parser *parser) {
    parser_seek_token(parser, TOKEN_LOOP);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    ast_node_scope *node_scope = parser_parse_scope(parser);

    return ast_node_loop_create(node_expr, node_scope);
}