#include "modules/parser/asst.h"
#include "modules/parser/var.h"
#include "modules/parser/expr.h"

ast_node_asst *parser_parse_asst(parser *parser) {
    ast_node_var *node_var = parser_parse_var(parser);
    parser_seek_token(parser, TOKEN_LARROW);
    ast_node_expr *node_expr = parser_parse_expr(parser);
    parser_seek_token(parser, TOKEN_DOT);

    return ast_node_asst_create(node_var, node_expr);
}