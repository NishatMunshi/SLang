#include "modules/parser/ast_nodes/call.h"
#include "modules/parser/ast_nodes/expr.h"

static list *parser_parse_call_args(parser *parser) {
    parser_seek_token(parser, TOKEN_LPAREN);

    list *args_list = list_create();
    if (token_get_type(parser_current_token(parser)) != TOKEN_RPAREN) {
        list_push(args_list, parser_parse_expr(parser));
        while (token_get_type(parser_current_token(parser)) == TOKEN_COMMA) {
            parser_advance(parser);
            list_push(args_list, parser_parse_expr(parser));
        }
    }
    parser_seek_token(parser, TOKEN_RPAREN);

    return args_list;
}

ast_node_call *parser_parse_call(parser *parser) {
    token *name = parser_seek_token(parser, TOKEN_IDENT);
    list *args_list = parser_parse_call_args(parser);

    return ast_node_call_create(name, args_list);
}