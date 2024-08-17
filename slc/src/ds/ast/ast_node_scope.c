#include "ds/ast/ast_node_scope.h"
#include "memory/arena_allocator.h"

struct ast_node_scope_struct {
    size_t num_local_vars;
    list *stmts;
};

ast_node_scope *ast_node_scope_create() {
    ast_node_scope *node_scope = arena_allocator_allocate(sizeof(struct ast_node_scope_struct));
    node_scope->stmts = list_create();
    return node_scope;
}

void ast_node_scope_add_stmt(ast_node_scope *node_scope, ast_node_stmt *node_stmt) {
    list_push(node_scope->stmts, node_stmt);
}

void ast_node_scope_set_num_local_vars(ast_node_scope *node_scope, size_t num) {
    node_scope->num_local_vars = num;
}

size_t ast_node_scope_get_num_local_vars(ast_node_scope *node_scope) {
    return node_scope->num_local_vars;
}

list *ast_node_scope_get_stmts(ast_node_scope *node_scope) {
    return node_scope->stmts;
}
