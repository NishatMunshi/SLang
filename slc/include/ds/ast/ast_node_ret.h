#ifndef SLC_AST_NODE_RET_H
#define SLC_AST_NODE_RET_H

#include "ds/ast/ast_node_expr.h"

typedef struct ast_node_ret_struct ast_node_ret;

ast_node_ret *ast_node_ret_create(ast_node_expr *node_expr);

ast_node_expr *ast_node_ret_get_expr(ast_node_ret *node_ret);

#endif // SLC_AST_NODE_RET_H