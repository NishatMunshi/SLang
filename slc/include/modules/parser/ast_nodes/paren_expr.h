#ifndef SLC_MODULES_PARSER_AST_NODES_PAREN_EXPR_H
#define SLC_MODULES_PARSER_AST_NODES_PAREN_EXPR_H

#include "ds/ast/nodes/paren_expr.h"
#include "modules/parser/parser.h"

ast_node_paren_expr *parser_parse_paren_expr(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_PAREN_EXPR_H