#include "modules/parser/ast_nodes/func.h"

#include "modules/parser/ast_nodes/scope.h"
#include "modules/parser/ast_nodes/var.h"

static list *parser_parse_func_params(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);

    list *params_list = list_create();
    if (token_get_type(parser_current_token(parser)) == TOKEN_IDENT) {
        ast_node_var *param = parser_parse_var(parser);
        list_push(params_list, param);
        while (token_get_type(parser_current_token(parser)) == TOKEN_COMMA) {
            parser_advance(parser);
            param = parser_parse_var(parser);
            list_push(params_list, param);
        }
    }

    parser_seek_token(parser, TOKEN_RPAREN);

    return params_list;
}

ast_node_func *parser_parser_func(parser *parser) {
    parser_seek_token(parser, TOKEN_FUNC);
    token *name = parser_seek_token(parser, TOKEN_IDENT);
    parser_seek_token(parser, TOKEN_COLON);
    list *params_list = parser_parse_func_params(parser);
    parser_seek_token(parser, TOKEN_DEFN);
    ast_node_scope *node_scope = parser_parse_scope(parser);
    return ast_node_func_create(name, params_list, node_scope);
}