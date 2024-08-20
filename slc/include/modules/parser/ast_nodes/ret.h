#ifndef SLC_MODULES_PARSER_AST_NODES_RET_H
#define SLC_MODULES_PARSER_AST_NODES_RET_H

#include "ds/ast/nodes/ret.h"
#include "modules/parser/parser.h"

ast_node_ret *parser_parse_ret(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_RET_H