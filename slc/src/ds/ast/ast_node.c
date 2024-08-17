#include "ds/ast/ast_node.h"
#include "memory/arena_allocator.h"
#include "ds/token/token.h"

#include <stdio.h>

struct ast_node_prog_struct {
    list *funcs;
};

ast_node_prog *ast_node_prog_create(list *funcs_list) {
    ast_node_prog *node_prog = arena_allocator_allocate(sizeof(struct ast_node_prog_struct));
    node_prog->funcs = funcs_list;
    return node_prog;
}

list *ast_node_prog_get_funcs(ast_node_prog *node_prog) {
    return node_prog->funcs;
}

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
token *ast_node_func_get_name_token(ast_node_func *node_func) { return node_func->name; }
list *ast_node_func_get_params(ast_node_func *node_func) { return node_func->params; }
ast_node_scope *ast_node_func_get_scope(ast_node_func *node_func) { return node_func->scope; }

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

struct ast_node_call_struct {
    token *name;
    list *args;
};

ast_node_call *ast_node_call_create(token *name, list *args) {
    ast_node_call *node_call = arena_allocator_allocate(sizeof(struct ast_node_call_struct));
    node_call->name = name;
    node_call->args = args;

    return node_call;
}
token *ast_node_call_get_name(ast_node_call *node_call) { return node_call->name; }
list *ast_node_call_get_args(ast_node_call *node_call) { return node_call->args; }

struct ast_node_bin_expr_struct {
    ast_node_bin_expr_type bin_expr_type;
    ast_node_expr *node_expr_left;
    ast_node_un_expr *node_un_expr_right;
};

ast_node_bin_expr *ast_node_bin_expr_create(ast_node_bin_expr_type bin_expr_type, ast_node_expr *node_expr_left, ast_node_un_expr *node_un_expr_right) {
    ast_node_bin_expr *node_bin_expr = arena_allocator_allocate(sizeof(struct ast_node_bin_expr_struct));
    node_bin_expr->bin_expr_type = bin_expr_type;
    node_bin_expr->node_expr_left = node_expr_left;
    node_bin_expr->node_un_expr_right = node_un_expr_right;

    return node_bin_expr;
}

ast_node_bin_expr *ast_node_bin_expr_create_add(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right) {
    return ast_node_bin_expr_create(AST_NODE_BIN_EXPR_ADD, node_expr_left, node_expr_un_right);
}
ast_node_bin_expr *ast_node_bin_expr_create_sub(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right) {
    return ast_node_bin_expr_create(AST_NODE_BIN_EXPR_SUB, node_expr_left, node_expr_un_right);
}
void ast_node_bin_expr_add_right(ast_node_bin_expr *node_bin_expr, ast_node_un_expr *node_expr_un_right) {
    node_bin_expr->node_un_expr_right = node_expr_un_right;
}

ast_node_bin_expr_type ast_node_bin_expr_get_type(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->bin_expr_type;
}

ast_node_expr *ast_node_bin_expr_get_left(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->node_expr_left;
}
ast_node_un_expr *ast_node_bin_expr_get_right(ast_node_bin_expr *node_bin_expr) {
    return node_bin_expr->node_un_expr_right;
}

struct ast_node_var_struct {
    token *var_name_token;
    long offset; // wrt rbp
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

struct ast_node_num_struct {
    string_view *num_value;
};

ast_node_num *ast_node_num_create(string_view *num_value) {
    ast_node_num *node_num = arena_allocator_allocate(sizeof(struct ast_node_num_struct));
    node_num->num_value = num_value;

    return node_num;
}

string_view *ast_node_num_get_value(ast_node_num *node_num) {
    return node_num->num_value;
}