#ifndef SLC_MODULES_PARSER_DECL_H
#define SLC_MODULES_PARSER_DECL_H

#include "modules/parser/parser.h"
#include "ds/ast/nodes/decl.h"

ast_node_decl *parser_parse_decl(parser *parser);

#endif // SLC_MODULES_PARSER_DECL_H
