#ifndef SLC_MODULES_PARSER_AST_NODES_COND_H
#define SLC_MODULES_PARSER_AST_NODES_COND_H

#include "ds/ast/nodes/cond.h"
#include "modules/parser/parser.h"

ast_node_cond *parser_parse_cond(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_COND_H