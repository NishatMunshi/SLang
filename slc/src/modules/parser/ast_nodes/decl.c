#include "modules/parser/ast_nodes/decl.h"
#include "modules/parser/ast_nodes/asst.h"

ast_node_decl *parser_parse_decl(parser *parser) {
    parser_seek_token(parser, TOKEN_VAR);
    return parser_parse_asst(parser);
}