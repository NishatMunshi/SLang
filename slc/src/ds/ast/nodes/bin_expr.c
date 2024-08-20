#include "ds/ast/nodes/bin_expr.h"

#include "memory/arena_allocator.h"

struct ast_node_bin_expr_struct {
    ast_node_bin_expr_type bin_expr_type;
    ast_node_expr *node_expr_left;
    ast_node_un_expr *node_un_expr_right;
};

ast_node_bin_expr *ast_node_bin_expr_create(ast_node_bin_expr_type bin_expr_type, ast_node_expr *node_expr_left, ast_node_un_expr *node_un_expr_right) {
    ast_node_bin_expr *node_bin_expr = arena_allocator_allocate(sizeof(struct ast_node_bin_expr_struct));
    node_bin_expr->bin_expr_type = bin_expr_type;
    node_bin_expr->node_expr_left = node_expr_left;
    node_bin_expr->node_un_expr_right = node_un_expr_right;

    return node_bin_expr;
}

ast_node_bin_expr *ast_node_bin_expr_create_add(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right) {
    return ast_node_bin_expr_create(AST_NODE_BIN_EXPR_ADD, node_expr_left, node_expr_un_right);
}

ast_node_bin_expr *ast_node_bin_expr_create_sub(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right) {
    return ast_node_bin_expr_create(AST_NODE_BIN_EXPR_SUB, node_expr_left, node_expr_un_right);
}

void ast_node_bin_expr_add_right(ast_node_bin_expr *node_bin_expr, ast_node_un_expr *node_expr_un_right) {
    node_bin_expr->node_un_expr_right = node_expr_un_right;
}

ast_node_bin_expr_type ast_node_bin_expr_get_type(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->bin_expr_type;
}

ast_node_expr *ast_node_bin_expr_get_left(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->node_expr_left;
}

ast_node_un_expr *ast_node_bin_expr_get_right(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->node_un_expr_right;
}