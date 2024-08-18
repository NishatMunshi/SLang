#ifndef SLC_MODULES_PARSER_SCOPE_H
#define SLC_MODULES_PARSER_SCOPE_H

#include "modules/parser/parser.h"
#include "ds/ast/nodes/scope.h"

ast_node_scope *parser_parse_scope(parser *parser);

#endif // SLC_MODULES_PARSER_SCOPE_H