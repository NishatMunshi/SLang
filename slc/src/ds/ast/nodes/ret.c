#include "ds/ast/nodes/ret.h"

#include "memory/arena_allocator.h"

struct ast_node_ret_struct {
    ast_node_expr *node_expr;
};

ast_node_ret *ast_node_ret_create(ast_node_expr *node_expr) {
    ast_node_ret *node_ret = arena_allocator_allocate(sizeof(struct ast_node_ret_struct));
    node_ret->node_expr = node_expr;

    return node_ret;
}

ast_node_expr *ast_node_ret_get_expr(ast_node_ret *node_ret) {
    return node_ret->node_expr;
}