#include "ds/ast/nodes/func.h"

#include "memory/arena_allocator.h"

struct ast_node_func_struct {
    token *name;
    list *params;
    ast_node_scope *scope;
};

ast_node_func *ast_node_func_create(token *name, list *params, ast_node_scope *node_scope) {
    ast_node_func *node_func = arena_allocator_allocate(sizeof(struct ast_node_func_struct));
    node_func->name = name;
    node_func->params = params;
    node_func->scope = node_scope;

    return node_func;
}

token *ast_node_func_get_name_token(ast_node_func *node_func) {
    return node_func->name;
}

list *ast_node_func_get_params(ast_node_func *node_func) {
    return node_func->params;
}

ast_node_scope *ast_node_func_get_scope(ast_node_func *node_func) {
    return node_func->scope;
}
