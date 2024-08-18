#include "modules/parser/decl.h"
#include "modules/parser/asst.h"

ast_node_decl *parser_parse_decl(parser *parser) {
    parser_seek_token(parser, TOKEN_VAR);
    return parser_parse_asst(parser);
}