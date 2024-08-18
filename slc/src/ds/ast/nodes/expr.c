#include "ds/ast/nodes/expr.h"
#include "memory/arena_allocator.h"

struct ast_node_expr_struct {
    ast_node_expr_type expr_type;
    union {
        ast_node_un_expr *node_un_expr;
        ast_node_bin_expr *node_bin_expr;
    } ast_node;
};

static ast_node_expr *ast_node_expr_create(ast_node_expr_type expr_type) {
    ast_node_expr *node_expr = arena_allocator_allocate(sizeof(struct ast_node_expr_struct));
    node_expr->expr_type = expr_type;

    return node_expr;
}

ast_node_expr *ast_node_expr_create_un_expr(ast_node_un_expr *node_un_expr) {
    ast_node_expr *node_expr = ast_node_expr_create(AST_NODE_EXPR_UN_EXPR);
    node_expr->ast_node.node_un_expr = node_un_expr;
    return node_expr;
}

ast_node_expr *ast_node_expr_create_bin_expr(ast_node_bin_expr *node_bin_expr) {
    ast_node_expr *node_expr = ast_node_expr_create(AST_NODE_EXPR_BIN_EXPR);
    node_expr->ast_node.node_bin_expr = node_bin_expr;
    return node_expr;
}

ast_node_expr_type ast_node_expr_get_type(ast_node_expr *node_expr) {
    return node_expr->expr_type;
}

ast_node_un_expr *ast_node_expr_get_un_expr(ast_node_expr *node_expr) {
    return node_expr->ast_node.node_un_expr;
}

ast_node_bin_expr *ast_node_expr_get_bin_expr(ast_node_expr *node_expr) {
    return node_expr->ast_node.node_bin_expr;
}