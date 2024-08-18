#ifndef SLC_DS_AST_NODES_COND_H
#define SLC_DS_AST_NODES_COND_H

#include "ds/ast/nodes/expr.h"
#include "ds/ast/nodes/scope.h"

typedef struct ast_node_cond_struct ast_node_cond;
typedef struct ast_node_scope_struct ast_node_scope;

ast_node_cond *ast_node_cond_create(ast_node_expr *node_expr, ast_node_scope *node_scope);

ast_node_expr * ast_node_cond_get_expr(ast_node_cond *node_cond);
ast_node_scope *ast_node_cond_get_scope(ast_node_cond *node_cond);

#endif // SLC_DS_AST_NODES_COND_H