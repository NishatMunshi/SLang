#ifndef SLC_MODULES_PARSER_EXPR_H
#define SLC_MODULES_PARSER_EXPR_H

#include "modules/parser/parser.h"
#include "ds/ast/nodes/expr.h"

ast_node_expr *parser_parse_expr(parser *parser);

#endif // SLC_MODULES_PARSER_EXPR_H
