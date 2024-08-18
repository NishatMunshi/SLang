#ifndef SLC_MODULES_PARSER_AST_NODES_COND_H
#define SLC_MODULES_PARSER_AST_NODES_COND_H

#include "modules/parser/parser.h"
#include "ds/ast/nodes/cond.h"

ast_node_cond *parser_parse_cond(parser *parser);

#endif // SLC_MODULES_PARSER_AST_NODES_COND_H