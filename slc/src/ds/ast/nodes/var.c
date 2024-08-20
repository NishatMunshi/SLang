#include "ds/ast/nodes/var.h"

#include "memory/arena_allocator.h"

struct ast_node_var_struct {
    token *var_name_token;
    long offset;  // wrt rbp
};

ast_node_var *ast_node_var_create(token *var_name_token) {
    ast_node_var *node_var = arena_allocator_allocate(sizeof(struct ast_node_var_struct));
    node_var->var_name_token = var_name_token;

    return node_var;
}

string_view *ast_node_var_get_name(ast_node_var *node_var) {
    return token_get_name(node_var->var_name_token);
}

void ast_node_var_set_offset(ast_node_var *node_var, long offset) {
    node_var->offset = offset;
}

long ast_node_var_get_offset(ast_node_var *node_var) {
    return node_var->offset;
}

token *ast_node_var_get_token(ast_node_var *node_var) {
    return node_var->var_name_token;
}
