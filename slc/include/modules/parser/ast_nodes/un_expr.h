#ifndef SLC_MODULES_PARSER_AST_NODES_UN_EXPR_H
#define SLC_MODULES_PARSER_AST_NODES_UN_EXPR_H

#include "ds/ast/nodes/un_expr.h"
#include "modules/parser/parser.h"

ast_node_un_expr *parser_parse_un_expr(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_UN_EXPR_H