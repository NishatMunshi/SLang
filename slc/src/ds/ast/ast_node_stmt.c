#include "ds/ast/ast_node_stmt.h"
#include "memory/arena_allocator.h"

struct ast_node_stmt_struct {
    ast_node_stmt_type stmt_type;
    union {
        ast_node_decl *node_decl;
        ast_node_asst *node_asst;
        ast_node_cond *node_cond;
        ast_node_loop *node_loop;
        ast_node_ret *node_ret;
    } ast_node;
};

static ast_node_stmt *ast_node_stmt_create(ast_node_stmt_type type) {
    ast_node_stmt *node_stmt = arena_allocator_allocate(sizeof(struct ast_node_stmt_struct));
    node_stmt->stmt_type = type;
    return node_stmt;
}

ast_node_stmt *ast_node_stmt_create_decl(ast_node_decl *node_decl) {
    ast_node_stmt *node_stmt = ast_node_stmt_create(AST_NODE_STMT_DECL);
    node_stmt->ast_node.node_decl = node_decl;
    return node_stmt;
}

ast_node_stmt *ast_node_stmt_create_asst(ast_node_asst *node_asst) {
    ast_node_stmt *node_stmt = ast_node_stmt_create(AST_NODE_STMT_ASST);
    node_stmt->ast_node.node_decl = node_asst;
    return node_stmt;
}
ast_node_stmt *ast_node_stmt_create_cond(ast_node_cond *node_cond) {
    ast_node_stmt *node_stmt = ast_node_stmt_create(AST_NODE_STMT_COND);
    node_stmt->ast_node.node_cond = node_cond;
    return node_stmt;
}

ast_node_stmt *ast_node_stmt_create_loop(ast_node_loop *node_loop) {
    ast_node_stmt *node_stmt = ast_node_stmt_create(AST_NODE_STMT_LOOP);
    node_stmt->ast_node.node_loop = node_loop;
    return node_stmt;
}

ast_node_stmt *ast_node_stmt_create_ret(ast_node_ret *node_ret) {
    ast_node_stmt *node_stmt = ast_node_stmt_create(AST_NODE_STMT_RET);
    node_stmt->ast_node.node_ret = node_ret;
    return node_stmt;
}

ast_node_stmt_type ast_node_stmt_get_type(ast_node_stmt *node_stmt) {
    return node_stmt->stmt_type;
}

ast_node_decl *ast_node_stmt_get_decl(ast_node_stmt *node_stmt) {
    return node_stmt->ast_node.node_decl;
}

ast_node_asst *ast_node_stmt_get_asst(ast_node_stmt *node_stmt) {
    return node_stmt->ast_node.node_asst;
}

ast_node_cond *ast_node_stmt_get_cond(ast_node_stmt *node_stmt) {
    return node_stmt->ast_node.node_cond;
}

ast_node_ret *ast_node_stmt_get_ret(ast_node_stmt *node_stmt) {
    return node_stmt->ast_node.node_ret;
}
