#ifndef SLC_DS_AST_NODES_ASST_H
#define SLC_DS_AST_NODES_ASST_H

#include "ds/ast/nodes/decl.h"

typedef struct ast_node_decl_struct ast_node_asst;

#define ast_node_asst_create ast_node_decl_create

#define ast_node_asst_get_var ast_node_decl_get_var
#define ast_node_asst_get_rhs ast_node_decl_get_rhs

#endif  // SLC_DS_AST_NODES_ASST_H
