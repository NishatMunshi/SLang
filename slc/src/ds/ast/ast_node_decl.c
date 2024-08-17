#include "ds/ast/ast_node_decl.h"
#include "memory/arena_allocator.h"

struct ast_node_decl_struct {
    ast_node_var *var;
    ast_node_expr *rhs;
};

ast_node_decl *ast_node_decl_create(ast_node_var *node_var, ast_node_expr *node_expr) {
    ast_node_decl *node_decl = arena_allocator_allocate(sizeof(struct ast_node_decl_struct));
    node_decl->var = node_var;
    node_decl->rhs = node_expr;

    return node_decl;
}

ast_node_expr *ast_node_decl_get_rhs(ast_node_decl *node_decl) {
    return node_decl->rhs;
}

ast_node_var *ast_node_decl_get_var(ast_node_decl *node_decl) {
    return node_decl->var;
}