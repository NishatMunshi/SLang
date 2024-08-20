#include "modules/parser/ast_nodes/scope.h"

#include "modules/parser/ast_nodes/stmt.h"

ast_node_scope *parser_parse_scope(parser *parser) {
    parser_seek_token(parser, TOKEN_LBRACE);
    ast_node_scope *node_scope = ast_node_scope_create();
    for (ast_node_stmt *node_stmt = parser_parse_stmt(parser);
         node_stmt != NULL;
         node_stmt = parser_parse_stmt(parser)) {
        ast_node_scope_add_stmt(node_scope, node_stmt);
    }
    parser_seek_token(parser, TOKEN_RBRACE);

    return node_scope;
}