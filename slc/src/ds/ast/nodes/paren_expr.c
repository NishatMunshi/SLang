#include "ds/ast/nodes/paren_expr.h"
#include "memory/arena_allocator.h"

struct ast_node_paren_expr_struct {
    ast_node_expr *node_expr;
};

ast_node_paren_expr *ast_node_paren_expr_create(ast_node_expr *node_expr) {
    ast_node_paren_expr *node_paren_expr = arena_allocator_allocate(sizeof(struct ast_node_paren_expr_struct));
    node_paren_expr->node_expr = node_expr;

    return node_paren_expr;
}

ast_node_expr *ast_node_paren_expr_get_expr(ast_node_paren_expr *node_paren_expr) {
    return node_paren_expr->node_expr;
}
