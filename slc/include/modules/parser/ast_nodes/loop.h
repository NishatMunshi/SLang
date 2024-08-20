#ifndef SLC_MODULES_PARSER_AST_NODES_LOOP_H
#define SLC_MODULES_PARSER_AST_NODES_LOOP_H

#include "ds/ast/nodes/loop.h"
#include "modules/parser/parser.h"

ast_node_loop *parser_parse_loop(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_LOOP_H