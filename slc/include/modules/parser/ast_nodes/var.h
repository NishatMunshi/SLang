#ifndef SLC_MODULES_PARSER_AST_NODES_VAR_H
#define SLC_MODULES_PARSER_AST_NODES_VAR_H

#include "ds/ast/nodes/var.h"
#include "modules/parser/parser.h"

ast_node_var *parser_parse_var(parser *parser);

#endif // SLC_MODULES_PARSER_AST_NODES_VAR_H