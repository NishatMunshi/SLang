#include "../include/ast_verifier.h"
#include "../include/arena_allocator.h"
#include "../include/slc.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ast_verifier_struct {
    list *funcs_list;
    list *vars_list;
    bool enter_exists;
    list_node *scope_end_var;
} ast_verifier;

static ast_verifier *ast_verifier_create() {
    ast_verifier *verifier = arena_allocator_allocate(sizeof(struct ast_verifier_struct));
    verifier->funcs_list = list_create();
    verifier->vars_list = NULL;
    verifier->enter_exists = false;

    return verifier;
}

static void ast_verifier_set_enter_exists(ast_verifier *verifier) {
    verifier->enter_exists = true;
}

static bool ast_verifier_enter_exists(ast_verifier *verifier) {
    return verifier->enter_exists;
}

static void ast_verifier_add_func(ast_verifier *verifier, ast_node_func *node_func) {
    list_push(verifier->funcs_list, node_func);
}

static void ast_verifier_add_var(ast_verifier *verifier, ast_node_var *node_var) {
    list_push(verifier->vars_list, node_var);
}

static void ast_verifier_reset_vars_list(ast_verifier *verifier) {
    verifier->vars_list = list_create();
}

static size_t ast_verifier_get_num_vars(ast_verifier *verifier) {
    return list_get_size(verifier->vars_list);
}

static void ast_verifier_enter_scope(ast_verifier *verifier) {
    verifier->scope_end_var = list_get_end(verifier->vars_list);
}

static void ast_verifier_leave_scope(ast_verifier *verifier) {
    list_chop_after_and_including(verifier->vars_list, verifier->scope_end_var);
}

static ast_node_var *ast_verifier_vars_list_contains_var(list *vars_list, string_view *var_name) {
    list_for_each(ast_node_var, var, vars_list) {
        if (string_view_compare(ast_node_var_get_name(var), var_name)) {
            return var;
        }
    }
    return NULL;
}

static ast_node_func *ast_verifier_funcs_list_contains_func(list *funcs_list, string_view *func_name) {
    list_for_each(ast_node_func, func, funcs_list) {
        if (string_view_compare(token_get_name(ast_node_func_get_name_token(func)), func_name)) {
            return func;
        }
    }
    return NULL;
}

#define AST_VERIFIER_ERROR() printf("[AST_VERIFIER ERROR]: ")

static void ast_verifier_verify_var_name_is_new(token *var_name_token, ast_verifier *verifier) {
    if (ast_verifier_vars_list_contains_var(verifier->vars_list, token_get_name(var_name_token))) {
        slc_print_compiler_execuatable_name();
        token_print_pos(var_name_token);
        AST_VERIFIER_ERROR();
        printf("variable '");
        string_view_print(token_get_name(var_name_token));
        printf("' is already defined.\n");
        exit(1);
    }
}

static long ast_verifier_calc_new_var_offset(ast_verifier *verifier) {
    ast_node_var *last_node_var = list_get_back(verifier->vars_list);
    long offset = 0;
    if (last_node_var) {
        offset = ast_node_var_get_offset(last_node_var);
    }
    return (offset >= 0) ? -sizeof(size_t) : (offset - sizeof(size_t));
}

static ast_node_var *ast_verifier_verify_var_exists(token *var_name_token, ast_verifier *verifier) {
    ast_node_var *list_var = ast_verifier_vars_list_contains_var(verifier->vars_list, token_get_name(var_name_token));
    if (list_var) {
        return list_var;
    }
    slc_print_compiler_execuatable_name();
    token_print_pos(var_name_token);
    AST_VERIFIER_ERROR();
    printf("variable '");
    string_view_print(token_get_name(var_name_token));
    printf("' is not defined.\n");
    exit(1);
}

static void ast_verifier_verify_func_name_is_new(token *func_name_token, ast_verifier *verifier) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(verifier->funcs_list, token_get_name(func_name_token));
    if (node_func) {
        slc_print_compiler_execuatable_name();
        token_print_pos(func_name_token);
        AST_VERIFIER_ERROR();
        printf("function '");
        string_view_print(token_get_name(func_name_token));
        printf("' is already defined.\n");
        exit(1);
    }
}

static ast_node_func *ast_verifier_verify_func_exists(token *func_name_token, ast_verifier *verifier) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(verifier->funcs_list, token_get_name(func_name_token));
    if (node_func) {
        return node_func;
    }
    slc_print_compiler_execuatable_name();
    token_print_pos(func_name_token);
    AST_VERIFIER_ERROR();
    printf("function '");
    string_view_print(token_get_name(func_name_token));
    printf("' is not defined.\n");
    exit(1);
}

// -------------------------------------------------------------------------------------------------------------

static void ast_verifier_check_num_args(ast_node_call *node_call, ast_node_func *node_func) {
    if (list_get_size(ast_node_func_get_params(node_func)) != list_get_size(ast_node_call_get_args(node_call))) {
        slc_print_compiler_execuatable_name();
        token_print_pos(ast_node_call_get_name(node_call));
        AST_VERIFIER_ERROR();
        printf("incorrect number of arguments in function call: ");
        string_view_print(token_get_name(ast_node_call_get_name(node_call)));
        printf("\n");
        exit(1);
    }
}

static void ast_verifier_verify_expr(ast_node_expr *node_expr, ast_verifier *verifier);

static void ast_verifier_verify_call(ast_node_call *node_call, ast_verifier *verifier) {
    ast_node_func *node_func = ast_verifier_verify_func_exists(ast_node_call_get_name(node_call), verifier);
    ast_verifier_check_num_args(node_call, node_func);
    list_for_each(ast_node_expr, expr, ast_node_call_get_args(node_call)) {
        ast_verifier_verify_expr(expr, verifier);
    }
}

static void ast_verifier_verify_un_expr(ast_node_un_expr *node_un_expr, ast_verifier *verifier) {
    switch (ast_node_un_expr_get_type(node_un_expr)) {
    case AST_NODE_UN_EXPR_NUM: break;
    case AST_NODE_UN_EXPR_VAR: {
        ast_node_var *node_var = ast_node_un_expr_get_var(node_un_expr);
        ast_node_var *list_var = ast_verifier_verify_var_exists(ast_node_var_get_token(node_var), verifier);
        ast_node_var_set_offset(node_var, ast_node_var_get_offset(list_var));
        }
        break;
    case AST_NODE_UN_EXPR_PAREN_EXPR: ast_verifier_verify_expr(ast_node_paren_expr_get_expr(ast_node_un_expr_get_paren_expr(node_un_expr)), verifier); break;
    case AST_NODE_UN_EXPR_CALL: ast_verifier_verify_call(ast_node_un_expr_get_call(node_un_expr), verifier); break;

    default: assert(false && "unreachable\n");
    }
}

static void ast_verifier_verify_bin_expr(ast_node_bin_expr *node_bin_expr, ast_verifier *verifier) {
    ast_verifier_verify_expr(ast_node_bin_expr_get_left(node_bin_expr), verifier);
    ast_verifier_verify_un_expr(ast_node_bin_expr_get_right(node_bin_expr), verifier);
}

static void ast_verifier_verify_expr(ast_node_expr *node_expr, ast_verifier *verifier) {
    switch (ast_node_expr_get_type(node_expr)) {
    case AST_NODE_EXPR_UN_EXPR: ast_verifier_verify_un_expr(ast_node_expr_get_un_expr(node_expr), verifier); break;
    case AST_NODE_EXPR_BIN_EXPR: ast_verifier_verify_bin_expr(ast_node_expr_get_bin_expr(node_expr), verifier); break;

    default: assert(false && "unreachable");
    }
}

static void ast_verifier_verify_decl(ast_node_decl *node_decl, ast_verifier *verifier) {
    ast_node_var *node_var = ast_node_decl_get_var(node_decl);
    ast_verifier_verify_var_name_is_new(ast_node_var_get_token(node_var), verifier);
    ast_verifier_verify_expr(ast_node_decl_get_rhs(node_decl), verifier);
    ast_node_var_set_offset(node_var, ast_verifier_calc_new_var_offset(verifier));
    ast_verifier_add_var(verifier, node_var);
}

static void ast_verifier_verify_asst(ast_node_asst *node_asst, ast_verifier *verifier) {
    ast_node_var *node_var = ast_node_asst_get_var(node_asst);
    ast_verifier_verify_var_exists(ast_node_var_get_token(node_var), verifier);
    ast_verifier_verify_expr(ast_node_asst_get_rhs(node_asst), verifier);
}

static void ast_verifier_verify_scope(ast_node_scope *node_scope, ast_verifier *verifier);

static void ast_verifier_verify_cond(ast_node_cond *node_cond, ast_verifier *verifier) {
    ast_verifier_verify_expr(ast_node_cond_get_expr(node_cond), verifier);
    ast_verifier_verify_scope(ast_node_cond_get_scope(node_cond), verifier);
}

#define ast_verifier_verify_loop ast_verifier_verify_cond

static void ast_verifier_verify_stmt(ast_node_stmt *node_stmt, ast_verifier *verifier) {
    switch (ast_node_stmt_get_type(node_stmt)) {
    case AST_NODE_STMT_DECL: ast_verifier_verify_decl(ast_node_stmt_get_decl(node_stmt), verifier); break;
    case AST_NODE_STMT_ASST: ast_verifier_verify_asst(ast_node_stmt_get_asst(node_stmt), verifier); break;
    case AST_NODE_STMT_COND: ast_verifier_verify_cond(ast_node_stmt_get_cond(node_stmt), verifier); break;
    case AST_NODE_STMT_LOOP: ast_verifier_verify_loop(ast_node_stmt_get_loop(node_stmt), verifier); break;
    case AST_NODE_STMT_RET: ast_verifier_verify_expr(ast_node_ret_get_expr(ast_node_stmt_get_ret(node_stmt)), verifier); break;

    default: assert(false && "unreachable");
    }
}

static void ast_verifier_verify_scope(ast_node_scope *node_scope, ast_verifier *verifier) {
    list *stmts = ast_node_scope_get_stmts(node_scope);
    size_t num_vars_higher_scope = ast_verifier_get_num_vars(verifier);

    ast_verifier_enter_scope(verifier);

    list_for_each(ast_node_stmt, stmt, stmts) {
        ast_verifier_verify_stmt(stmt, verifier);
    }
    size_t num_local_vars = ast_verifier_get_num_vars(verifier) - num_vars_higher_scope;
    ast_node_scope_set_num_local_vars(node_scope, num_local_vars);

    ast_verifier_leave_scope(verifier);
}

static void ast_verifier_verify_func_params(list *params, ast_verifier *verifier) {
    ast_verifier_reset_vars_list(verifier);
    long offset = sizeof(size_t) * (1 + list_get_size(params));
    list_for_each(ast_node_var, var, params) {
        ast_verifier_verify_var_name_is_new(ast_node_var_get_token(var), verifier);
        ast_node_var_set_offset(var, offset);
        offset -= sizeof(size_t);
        ast_verifier_add_var(verifier, var);
    }
}

static void ast_verifier_verify_func(ast_node_func *node_func, ast_verifier *verifier) {
    ast_verifier_verify_func_name_is_new(ast_node_func_get_name_token(node_func), verifier);
    ast_verifier_add_func(verifier, node_func);

    if (string_view_compare_with_ctr(token_get_name(ast_node_func_get_name_token(node_func)), "enter")) {
        ast_verifier_set_enter_exists(verifier);
    }

    ast_verifier_verify_func_params(ast_node_func_get_params(node_func), verifier);
    ast_verifier_verify_scope(ast_node_func_get_scope(node_func), verifier);
}

static void ast_verifier_verify_enter_exists(ast_verifier *verifier) {
    if (!ast_verifier_enter_exists(verifier)) {
        slc_print_compiler_execuatable_name();
        AST_VERIFIER_ERROR();
        printf("function \"enter\" not found.\n");
        exit(1);
    }
}

void ast_verifier_verify_prog(ast_node_prog *node_prog) {
    ast_verifier *verifier = ast_verifier_create();

    list_for_each(ast_node_func, func, ast_node_prog_get_funcs(node_prog)) {
        ast_verifier_verify_func(func, verifier);
    }

    ast_verifier_verify_enter_exists(verifier);
}
