#ifndef SLC_DS_AST_NODES_DECL_H
#define SLC_DS_AST_NODES_DECL_H

#include "ds/ast/nodes/expr.h"
#include "ds/ast/nodes/var.h"

typedef struct ast_node_decl_struct ast_node_decl;

ast_node_decl *ast_node_decl_create(ast_node_var *node_var, ast_node_expr *node_expr);

ast_node_var *ast_node_decl_get_var(ast_node_decl *node_decl);
ast_node_expr *ast_node_decl_get_rhs(ast_node_decl *node_decl);

#endif  // SLC_DS_AST_NODES_DECL_H