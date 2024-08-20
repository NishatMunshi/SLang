#include "ds/ast/nodes/un_expr.h"

#include "memory/arena_allocator.h"

struct ast_node_un_expr_struct {
    ast_node_un_expr_type un_expr_type;
    union {
        ast_node_num *node_num;
        ast_node_var *node_var;
        ast_node_paren_expr *node_paren_expr;
        ast_node_call *node_call;
    } ast_node;
};

static ast_node_un_expr *ast_node_un_expr_create(ast_node_un_expr_type type) {
    ast_node_un_expr *node_un_expr = arena_allocator_allocate(sizeof(struct ast_node_un_expr_struct));
    node_un_expr->un_expr_type = type;

    return node_un_expr;
}

ast_node_un_expr *ast_node_un_expr_create_num(ast_node_num *node_num) {
    ast_node_un_expr *node_un_expr = ast_node_un_expr_create(AST_NODE_UN_EXPR_NUM);
    node_un_expr->ast_node.node_num = node_num;

    return node_un_expr;
}

ast_node_un_expr *ast_node_un_expr_create_var(ast_node_var *node_var) {
    ast_node_un_expr *node_un_expr = ast_node_un_expr_create(AST_NODE_UN_EXPR_VAR);
    node_un_expr->ast_node.node_var = node_var;
    return node_un_expr;
}

ast_node_un_expr *ast_node_un_expr_create_paren_expr(ast_node_paren_expr *node_paren_expr) {
    ast_node_un_expr *node_un_expr = ast_node_un_expr_create(AST_NODE_UN_EXPR_PAREN_EXPR);
    node_un_expr->ast_node.node_paren_expr = node_paren_expr;
    return node_un_expr;
}

ast_node_un_expr *ast_node_un_expr_create_call(ast_node_call *node_call) {
    ast_node_un_expr *node_un_expr = ast_node_un_expr_create(AST_NODE_UN_EXPR_CALL);
    node_un_expr->ast_node.node_call = node_call;
    return node_un_expr;
}

ast_node_un_expr_type ast_node_un_expr_get_type(ast_node_un_expr *node_un_expr) {
    return node_un_expr->un_expr_type;
}

ast_node_num *ast_node_un_expr_get_num(ast_node_un_expr *node_un_expr) {
    return node_un_expr->ast_node.node_num;
}

ast_node_var *ast_node_un_expr_get_var(ast_node_un_expr *node_un_expr) {
    return node_un_expr->ast_node.node_var;
}

ast_node_paren_expr *ast_node_un_expr_get_paren_expr(ast_node_un_expr *node_un_expr) {
    return node_un_expr->ast_node.node_paren_expr;
}

ast_node_call *ast_node_un_expr_get_call(ast_node_un_expr *node_un_expr) {
    return node_un_expr->ast_node.node_call;
}
