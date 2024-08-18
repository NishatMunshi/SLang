#include "modules/parser/ast_nodes/un_expr.h"
#include "modules/parser/ast_nodes/num.h"
#include "modules/parser/ast_nodes/call.h"
#include "modules/parser/ast_nodes/var.h"
#include "modules/parser/ast_nodes/paren_expr.h"

ast_node_un_expr *parser_parse_un_expr(parser *parser) {
    token *current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
    case TOKEN_NUM: return ast_node_un_expr_create_num(parser_parse_num(parser));
    case TOKEN_IDENT:
        if (token_get_type(parser_next_token(parser)) == TOKEN_LPAREN) {
            return ast_node_un_expr_create_call(parser_parse_call(parser));
        }
        return ast_node_un_expr_create_var(parser_parse_var(parser));
    case TOKEN_LPAREN: return ast_node_un_expr_create_paren_expr(parser_parse_paren_expr(parser));

    default: PARSER_ERROR(current_token, "an unary expression");
    }
}