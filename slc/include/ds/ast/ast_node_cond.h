#ifndef SLC_AST_NODE_COND_H
#define SLC_AST_NODE_COND_H

#include "ds/ast/ast_node_expr.h"
#include "ds/ast/ast_node_scope.h"

typedef struct ast_node_cond_struct ast_node_cond;
typedef struct ast_node_scope_struct ast_node_scope;

ast_node_cond *ast_node_cond_create(ast_node_expr *node_expr, ast_node_scope *node_scope);

ast_node_expr * ast_node_cond_get_expr(ast_node_cond *node_cond);
ast_node_scope *ast_node_cond_get_scope(ast_node_cond *node_cond);

#endif // SLC_AST_NODE_COND_H