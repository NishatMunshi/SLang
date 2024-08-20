#ifndef SLC_DS_AST_NODES_EXPR_H
#define SLC_DS_AST_NODES_EXPR_H

#include "ds/ast/nodes/bin_expr.h"
#include "ds/ast/nodes/un_expr.h"

typedef struct ast_node_expr_struct ast_node_expr;
typedef struct ast_node_bin_expr_struct ast_node_bin_expr;
typedef struct ast_node_un_expr_struct ast_node_un_expr;

typedef enum ast_node_expr_type_enum {
    AST_NODE_EXPR_UN_EXPR,
    AST_NODE_EXPR_BIN_EXPR
} ast_node_expr_type;

ast_node_expr *ast_node_expr_create_un_expr(ast_node_un_expr *node_un_expr);
ast_node_expr *ast_node_expr_create_bin_expr(ast_node_bin_expr *node_bin_expr);

ast_node_expr_type ast_node_expr_get_type(ast_node_expr *node_expr);
ast_node_un_expr *ast_node_expr_get_un_expr(ast_node_expr *node_expr);
ast_node_bin_expr *ast_node_expr_get_bin_expr(ast_node_expr *node_expr);

#endif  // SLC_DS_AST_NODES_EXPR_H