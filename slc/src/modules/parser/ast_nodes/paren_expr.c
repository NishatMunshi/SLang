#include "modules/parser/ast_nodes/paren_expr.h"
#include "modules/parser/ast_nodes/expr.h"

ast_node_paren_expr *parser_parse_paren_expr(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);
    ast_node_paren_expr *node_paren_expr = ast_node_paren_expr_create(parser_parse_expr(parser));
    parser_seek_token(parser, TOKEN_RPAREN);

    return node_paren_expr;
}
