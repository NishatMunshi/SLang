#include "modules/parser/ast_nodes/prog.h"

#include "modules/parser/ast_nodes/func.h"
#include "modules/parser/ast_nodes/paren_expr.h"

ast_node_prog *parser_parse_prog(list *token_list) {
    parser *parser = parser_create(token_list);

    list *funcs_list = list_create();
    while (token_get_type(parser_current_token(parser)) != TOKEN_EOF) {
        list_push(funcs_list, parser_parser_func(parser));
    }

    return ast_node_prog_create(funcs_list);
}