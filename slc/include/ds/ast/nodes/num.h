#ifndef SLC_DS_AST_NODES_NUM_H
#define SLC_DS_AST_NODES_NUM_H

#include "ds/string/string_view.h"

typedef struct ast_node_num_struct ast_node_num;

ast_node_num *ast_node_num_create(string_view *num_value);

string_view *ast_node_num_get_value(ast_node_num *node_num);

#endif  // SLC_DS_AST_NODES_NUM_H