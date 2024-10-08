#ifndef SLC_DS_AST_NODES_PROG_H
#define SLC_DS_AST_NODES_PROG_H

#include "ds/list/list.h"

typedef struct ast_node_prog_struct ast_node_prog;

ast_node_prog *ast_node_prog_create(list *funcs);

list *ast_node_prog_get_funcs(ast_node_prog *node_prog);

#endif  // SLC_DS_AST_NODES_PROG_H