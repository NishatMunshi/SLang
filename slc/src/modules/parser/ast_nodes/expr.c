#include "modules/parser/ast_nodes/expr.h"

#include "modules/parser/ast_nodes/bin_expr.h"
#include "modules/parser/ast_nodes/un_expr.h"

ast_node_expr *parser_parse_expr(parser *parser) {
    token *current_token = parser_current_token(parser);
    ast_node_expr *node_expr = NULL;
    switch (token_get_type(current_token)) {
        case TOKEN_NUM:
        case TOKEN_IDENT:
        case TOKEN_LPAREN:
            node_expr = ast_node_expr_create_un_expr(parser_parse_un_expr(parser));
            break;

        default:
            PARSER_ERROR(current_token, "an expression");
    }
    do {
        current_token = parser_current_token(parser);
        switch (token_get_type(current_token)) {
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_LT:
            case TOKEN_GT:
                node_expr = ast_node_expr_create_bin_expr(parser_parse_bin_expr(parser, node_expr));
                break;

            default:
                return node_expr;
        }
    } while (true);
}