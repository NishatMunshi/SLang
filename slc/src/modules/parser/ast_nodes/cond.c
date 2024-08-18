#include "modules/parser/ast_nodes/cond.h"
#include "modules/parser/ast_nodes/expr.h"
#include "modules/parser/ast_nodes/scope.h"

ast_node_cond *parser_parse_cond(parser *parser) {
    parser_seek_token(parser, TOKEN_IF);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    ast_node_scope *node_scope = parser_parse_scope(parser);

    return ast_node_cond_create(node_expr, node_scope);
}
