#include "modules/parser/bin_expr.h"
#include "modules/parser/un_expr.h"

ast_node_bin_expr *parser_parse_bin_expr(parser *parser, ast_node_expr *node_expr_left) {
    ast_node_bin_expr *node_bin_expr = NULL;
    token *current_token = parser_current_token(parser);
    parser_advance(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_PLUS: node_bin_expr = ast_node_bin_expr_create_add(node_expr_left, NULL); break;
    case TOKEN_MINUS: node_bin_expr = ast_node_bin_expr_create_sub(node_expr_left, NULL); break;

    default: PARSER_ERROR(current_token, "an operand");
    }

    current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_NUM:
    case TOKEN_IDENT:
    case TOKEN_LPAREN:
        ast_node_bin_expr_add_right(node_bin_expr, parser_parse_un_expr(parser));
        return node_bin_expr;
        
    default: PARSER_ERROR(current_token, "an expression");
    }
}