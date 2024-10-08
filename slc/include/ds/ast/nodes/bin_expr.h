#ifndef SLC_DS_AST_NODES_BIN_EXPR_H
#define SLC_DS_AST_NODES_BIN_EXPR_H

typedef struct ast_node_bin_expr_struct ast_node_bin_expr;
typedef struct ast_node_un_expr_struct ast_node_un_expr;
typedef struct ast_node_expr_struct ast_node_expr;

typedef enum ast_node_bin_expr_type_enum {
    AST_NODE_BIN_EXPR_ADD,
    AST_NODE_BIN_EXPR_SUB,
    AST_NODE_BIN_EXPR_LT,
    AST_NODE_BIN_EXPR_GT,
    AST_NODE_BIN_EXPR_BITAND,
    AST_NODE_BIN_EXPR_BITOR,
    AST_NODE_BIN_EXPR_BITXOR,
} ast_node_bin_expr_type;

ast_node_bin_expr *ast_node_bin_expr_create_add(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_sub(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_lt(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_gt(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_and(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_or(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *ast_node_bin_expr_create_xor(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);

void ast_node_bin_expr_add_right(ast_node_bin_expr *node_bin_expr, ast_node_un_expr *node_expr_un_right);

ast_node_bin_expr_type ast_node_bin_expr_get_type(ast_node_bin_expr *node_bin_expr);
ast_node_expr *ast_node_bin_expr_get_left(ast_node_bin_expr *node_bin_expr);
ast_node_un_expr *ast_node_bin_expr_get_right(ast_node_bin_expr *node_bin_expr);

#endif  // SLC_DS_AST_NODES_BIN_EXPR_H
