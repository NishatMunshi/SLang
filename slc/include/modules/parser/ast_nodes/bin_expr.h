#ifndef SLC_MODULES_PARSER_AST_NODES_BIN_EXPR_H
#define SLC_MODULES_PARSER_AST_NODES_BIN_EXPR_H

#include "modules/parser/parser.h"
#include "ds/ast/nodes/bin_expr.h"

ast_node_bin_expr *parser_parse_bin_expr(parser *parser, ast_node_expr *node_expr_left);

#endif // SLC_MODULES_PARSER_AST_NODES_BIN_EXPR_H