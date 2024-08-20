#ifndef SLC_MODULES_PARSER_AST_NODES_STMT_H
#define SLC_MODULES_PARSER_AST_NODES_STMT_H

#include "ds/ast/nodes/stmt.h"
#include "modules/parser/parser.h"

ast_node_stmt *parser_parse_stmt(parser *parser);

#endif  // SLC_MODULES_PARSER_AST_NODES_STMT_H