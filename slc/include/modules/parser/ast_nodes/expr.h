#ifndef SLC_MODULES_PARSER_AST_NODES_EXPR_H
#define SLC_MODULES_PARSER_AST_NODES_EXPR_H

#include "ds/ast/nodes/expr.h"
#include "modules/parser/parser.h"

ast_node_expr *parser_parse_expr(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_EXPR_H
