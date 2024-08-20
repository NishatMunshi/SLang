#include "ds/ast/nodes/cond.h"

#include "memory/arena_allocator.h"

struct ast_node_cond_struct {
    ast_node_expr *node_expr;
    ast_node_scope *node_scope;
};

ast_node_cond *ast_node_cond_create(ast_node_expr *node_expr, ast_node_scope *node_scope) {
    ast_node_cond *node_cond = arena_allocator_allocate(sizeof(struct ast_node_cond_struct));
    node_cond->node_expr = node_expr;
    node_cond->node_scope = node_scope;
    return node_cond;
}

ast_node_expr *ast_node_cond_get_expr(ast_node_cond *node_cond) {
    return node_cond->node_expr;
}

ast_node_scope *ast_node_cond_get_scope(ast_node_cond *node_cond) {
    return node_cond->node_scope;
}
