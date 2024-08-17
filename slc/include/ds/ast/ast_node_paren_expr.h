#ifndef SLC_AST_NODE_PAREN_EXPR_H
#define SLC_AST_NODE_PAREN_EXPR_H

#include "ds/ast/ast_node_expr.h"

typedef struct ast_node_paren_expr_struct ast_node_paren_expr;
typedef struct ast_node_expr_struct ast_node_expr;

ast_node_paren_expr *ast_node_paren_expr_create(ast_node_expr *node_expr);

ast_node_expr *ast_node_paren_expr_get_expr(ast_node_paren_expr *node_paren_expr);

#endif // SLC_AST_NODE_PAREN_EXPR_H