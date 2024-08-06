#ifndef SLC_PARSER_H
#define SLC_PARSER_H

#include "ast_node.h"
#include "list.h"

ast_node_prog *parser_parse_prog(list *token_list);

#endif // SLC_PARSER_H