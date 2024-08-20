#include "modules/parser/ast_nodes/stmt.h"

#include "modules/parser/ast_nodes/asst.h"
#include "modules/parser/ast_nodes/cond.h"
#include "modules/parser/ast_nodes/decl.h"
#include "modules/parser/ast_nodes/loop.h"
#include "modules/parser/ast_nodes/ret.h"

ast_node_stmt *parser_parse_stmt(parser *parser) {
    token *current_token = parser_current_token(parser);
    switch (token_get_type(current_token)) {
        case TOKEN_VAR:
            return ast_node_stmt_create_decl(parser_parse_decl(parser));
        case TOKEN_IDENT:
            return ast_node_stmt_create_asst(parser_parse_asst(parser));
        case TOKEN_IF:
            return ast_node_stmt_create_cond(parser_parse_cond(parser));
        case TOKEN_LOOP:
            return ast_node_stmt_create_loop(parser_parse_loop(parser));
        case TOKEN_RET:
            return ast_node_stmt_create_ret(parser_parse_ret(parser));

        case TOKEN_EOF:
        case TOKEN_RBRACE:
            return NULL;

        default:
            PARSER_ERROR(current_token, "a statement");
    }
}