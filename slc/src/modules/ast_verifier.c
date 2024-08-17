#include "modules/ast_verifier.h"
#include "memory/arena_allocator.h"
#include "ui/ui.h"
#include "ds/stack/stack.h"
#include "utils/utils.h"
#include "ds/ast/ast_node_stmt.h"
#include "ds/ast/ast_node_var.h"
#include "ds/ast/ast_node_ret.h"
#include "ds/ast/ast_node_expr.h"
#include "ds/ast/ast_node_num.h"
#include "ds/ast/ast_node_scope.h"
#include "ds/ast/ast_node_un_expr.h"
#include "ds/ast/ast_node_decl.h"
#include "ds/ast/ast_node_asst.h"
#include "ds/ast/ast_node_prog.h"
#include "ds/ast/ast_node_call.h"
#include "ds/ast/ast_node_func.h"
#include "ds/ast/ast_node_cond.h"
#include "ds/ast/ast_node_bin_expr.h"
#include "ds/ast/ast_node_paren_expr.h"
#include "ds/ast/ast_node_loop.h"

#include <stdio.h>
#include <stdlib.h>

static struct ast_verifier_struct {
    list *funcs_list;
    stack *vars_stack;
    bool enter_exists;
    size_t var_stack_size_at_scope_entry;
} ast_verifier = {0};

static void ast_verifier_init() {
    ast_verifier.funcs_list = list_create();
    ast_verifier.vars_stack = stack_create();
    ast_verifier.enter_exists = false;
    ast_verifier.var_stack_size_at_scope_entry = 0;
}

static void ast_verifier_set_enter_exists() {
    ast_verifier.enter_exists = true;
}

static bool ast_verifier_enter_exists() {
    return ast_verifier.enter_exists;
}

static void ast_verifier_add_func(ast_node_func *node_func) {
    list_push(ast_verifier.funcs_list, node_func);
}

static void ast_verifier_add_var(ast_node_var *node_var) {
    stack_push(ast_verifier.vars_stack, node_var);
}

static void ast_verifier_reset_vars_list() {
    ast_verifier.vars_stack = stack_create();
}

static size_t ast_verifier_get_num_vars() {
    return stack_get_size(ast_verifier.vars_stack);
}

static void ast_verifier_enter_scope() {
    ast_verifier.var_stack_size_at_scope_entry = stack_get_size(ast_verifier.vars_stack);
}

static void ast_verifier_leave_scope() {
    size_t vars_stack_current_size = stack_get_size(ast_verifier.vars_stack);
    size_t items_to_pop = vars_stack_current_size - ast_verifier.var_stack_size_at_scope_entry;
    for(size_t i = 0; i < items_to_pop; ++i) {
        stack_pop(ast_verifier.vars_stack);
    }
}

static ast_node_var *ast_verifier_vars_list_contains_var(stack *vars_stack, string_view *var_name) {
    STACK_FOR_EACH(ast_node_var, var, vars_stack) {
        if (string_view_compare(ast_node_var_get_name(var), var_name)) {
            return var;
        }
    }
    return NULL;
}

static ast_node_func *ast_verifier_funcs_list_contains_func(list *funcs_list, string_view *func_name) {
    LIST_FOR_EACH(ast_node_func, func, funcs_list) {
        if (string_view_compare(token_get_name(ast_node_func_get_name_token(func)), func_name)) {
            return func;
        }
    }
    return NULL;
}

#define ast_verifier_ERROR(TOKEN, MESSAGE)      \
    printf("[SLC]: [ast_verifier ERROR]: ");    \
    token_print_pos(TOKEN);                     \
    printf(MESSAGE": ");                        \
    string_view_print(token_get_name(TOKEN));   \
    printf("\n");                               \
    exit(1);                                    \

static void ast_verifier_verify_var_name_is_new(token *var_name_token) {
    if (ast_verifier_vars_list_contains_var(ast_verifier.vars_stack, token_get_name(var_name_token))) {
        ast_verifier_ERROR(var_name_token, "variable is already defined");
    }
}

static long ast_verifier_calc_new_var_offset() {
    ast_node_var *last_node_var = stack_node_get_data(stack_get_top(ast_verifier.vars_stack));
    long offset = 0;
    if (last_node_var) {
        offset = ast_node_var_get_offset(last_node_var);
    }
    return (offset >= 0) ? -sizeof(size_t) : (offset - sizeof(size_t));
}

static ast_node_var *ast_verifier_verify_var_exists(token *var_name_token) {
    ast_node_var *list_var = ast_verifier_vars_list_contains_var(ast_verifier.vars_stack, token_get_name(var_name_token));
    if (list_var) {
        return list_var;
    }
    ast_verifier_ERROR(var_name_token, "variable is not defined");
}

static void ast_verifier_verify_func_name_is_new(token *func_name_token) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(ast_verifier.funcs_list, token_get_name(func_name_token));
    if (node_func) {
        ast_verifier_ERROR(func_name_token, "function is already defined");
    }
}

static ast_node_func *ast_verifier_verify_func_exists(token *func_name_token) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(ast_verifier.funcs_list, token_get_name(func_name_token));
    if (node_func) {
        return node_func;
    }
    ast_verifier_ERROR(func_name_token, "function is not defined");
}

// -------------------------------------------------------------------------------------------------------------

static void ast_verifier_check_num_args(ast_node_call *node_call, ast_node_func *node_func) {
    if (list_get_size(ast_node_func_get_params(node_func)) != list_get_size(ast_node_call_get_args(node_call))) {
        ast_verifier_ERROR(ast_node_call_get_name(node_call), "incorrect number of arguments in function call");
    }
}

static void ast_verifier_verify_expr(ast_node_expr *node_expr);

static void ast_verifier_verify_call(ast_node_call *node_call) {
    ast_node_func *node_func = ast_verifier_verify_func_exists(ast_node_call_get_name(node_call));
    ast_verifier_check_num_args(node_call, node_func);
    LIST_FOR_EACH(ast_node_expr, expr, ast_node_call_get_args(node_call)) {
        ast_verifier_verify_expr(expr);
    }
}

static void ast_verifier_verify_un_expr(ast_node_un_expr *node_un_expr) {
    switch (ast_node_un_expr_get_type(node_un_expr)) {
    case AST_NODE_UN_EXPR_NUM: break;
    case AST_NODE_UN_EXPR_VAR: {
        ast_node_var *node_var = ast_node_un_expr_get_var(node_un_expr);
        ast_node_var *list_var = ast_verifier_verify_var_exists(ast_node_var_get_token(node_var));
        ast_node_var_set_offset(node_var, ast_node_var_get_offset(list_var));
        }
        break;
    case AST_NODE_UN_EXPR_PAREN_EXPR: ast_verifier_verify_expr(ast_node_paren_expr_get_expr(ast_node_un_expr_get_paren_expr(node_un_expr))); break;
    case AST_NODE_UN_EXPR_CALL: ast_verifier_verify_call(ast_node_un_expr_get_call(node_un_expr)); break;

    default: UNREACHABLE();
    }
}

static void ast_verifier_verify_bin_expr(ast_node_bin_expr *node_bin_expr) {
    ast_verifier_verify_expr(ast_node_bin_expr_get_left(node_bin_expr));
    ast_verifier_verify_un_expr(ast_node_bin_expr_get_right(node_bin_expr));
}

static void ast_verifier_verify_expr(ast_node_expr *node_expr) {
    switch (ast_node_expr_get_type(node_expr)) {
    case AST_NODE_EXPR_UN_EXPR: ast_verifier_verify_un_expr(ast_node_expr_get_un_expr(node_expr)); break;
    case AST_NODE_EXPR_BIN_EXPR: ast_verifier_verify_bin_expr(ast_node_expr_get_bin_expr(node_expr)); break;

    default: UNREACHABLE();
    }
}

static void ast_verifier_verify_decl(ast_node_decl *node_decl) {
    ast_node_var *node_var = ast_node_decl_get_var(node_decl);
    ast_verifier_verify_var_name_is_new(ast_node_var_get_token(node_var));
    ast_verifier_verify_expr(ast_node_decl_get_rhs(node_decl));
    ast_node_var_set_offset(node_var, ast_verifier_calc_new_var_offset(ast_verifier));
    ast_verifier_add_var(node_var);
}

static void ast_verifier_verify_asst(ast_node_asst *node_asst) {
    ast_node_var *node_var = ast_node_asst_get_var(node_asst);
    ast_verifier_verify_var_exists(ast_node_var_get_token(node_var));
    ast_verifier_verify_expr(ast_node_asst_get_rhs(node_asst));
}

static void ast_verifier_verify_scope(ast_node_scope *node_scope);

static void ast_verifier_verify_cond(ast_node_cond *node_cond) {
    ast_verifier_verify_expr(ast_node_cond_get_expr(node_cond));
    ast_verifier_verify_scope(ast_node_cond_get_scope(node_cond));
}

#define ast_verifier_verify_loop ast_verifier_verify_cond

static void ast_verifier_verify_stmt(ast_node_stmt *node_stmt) {
    switch (ast_node_stmt_get_type(node_stmt)) {
    case AST_NODE_STMT_DECL: ast_verifier_verify_decl(ast_node_stmt_get_decl(node_stmt)); break;
    case AST_NODE_STMT_ASST: ast_verifier_verify_asst(ast_node_stmt_get_asst(node_stmt)); break;
    case AST_NODE_STMT_COND: ast_verifier_verify_cond(ast_node_stmt_get_cond(node_stmt)); break;
    case AST_NODE_STMT_LOOP: ast_verifier_verify_loop(ast_node_stmt_get_loop(node_stmt)); break;
    case AST_NODE_STMT_RET: ast_verifier_verify_expr(ast_node_ret_get_expr(ast_node_stmt_get_ret(node_stmt))); break;

    default: UNREACHABLE();
    }
}

static void ast_verifier_verify_scope(ast_node_scope *node_scope) {
    list *stmts = ast_node_scope_get_stmts(node_scope);
    size_t num_vars_higher_scope = ast_verifier_get_num_vars(ast_verifier);

    ast_verifier_enter_scope(ast_verifier);

    LIST_FOR_EACH(ast_node_stmt, stmt, stmts) {
        ast_verifier_verify_stmt(stmt);
    }
    size_t num_local_vars = ast_verifier_get_num_vars(ast_verifier) - num_vars_higher_scope;
    ast_node_scope_set_num_local_vars(node_scope, num_local_vars);

    ast_verifier_leave_scope(ast_verifier);
}

static void ast_verifier_verify_func_params(list *params) {
    ast_verifier_reset_vars_list(ast_verifier);
    long offset = sizeof(size_t) * (1 + list_get_size(params));
    LIST_FOR_EACH(ast_node_var, var, params) {
        ast_verifier_verify_var_name_is_new(ast_node_var_get_token(var));
        ast_node_var_set_offset(var, offset);
        offset -= sizeof(size_t);
        ast_verifier_add_var(var);
    }
}

static void ast_verifier_verify_func(ast_node_func *node_func) {
    ast_verifier_verify_func_name_is_new(ast_node_func_get_name_token(node_func));
    ast_verifier_add_func(node_func);

    if (string_view_compare_with_ctr(token_get_name(ast_node_func_get_name_token(node_func)), "enter")) {
        ast_verifier_set_enter_exists(ast_verifier);
    }

    ast_verifier_verify_func_params(ast_node_func_get_params(node_func));
    ast_verifier_verify_scope(ast_node_func_get_scope(node_func));
}

static void ast_verifier_verify_enter_exists() {
    if (!ast_verifier_enter_exists(ast_verifier)) {
        printf("[SLC]: [ast_verifier ERROR]: function \"enter\" not found.\n");
        exit(1);
    }
}

void ast_verifier_verify_prog(ast_node_prog *node_prog) {
    ast_verifier_init();

    LIST_FOR_EACH(ast_node_func, func, ast_node_prog_get_funcs(node_prog)) {
        ast_verifier_verify_func(func);
    }

    ast_verifier_verify_enter_exists(ast_verifier);
}
