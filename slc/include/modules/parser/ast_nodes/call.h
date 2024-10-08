#ifndef SLC_MODULES_PARSER_AST_NODES_CALL_H
#define SLC_MODULES_PARSER_AST_NODES_CALL_H

#include "ds/ast/nodes/call.h"
#include "modules/parser/parser.h"

ast_node_call *parser_parse_call(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_CALL_H