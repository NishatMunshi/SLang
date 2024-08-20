#ifndef SLC_MODULES_PARSER_AST_NODES_SCOPE_H
#define SLC_MODULES_PARSER_AST_NODES_SCOPE_H

#include "ds/ast/nodes/scope.h"
#include "modules/parser/parser.h"

ast_node_scope *parser_parse_scope(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_SCOPE_H