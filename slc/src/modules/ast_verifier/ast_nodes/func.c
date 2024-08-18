#include "modules/ast_verifier/ast_nodes/func.h"
#include "modules/ast_verifier/ast_nodes/scope.h"

static void ast_verifier_verify_func_name_is_new(ast_verifier *ast_verifier, token *func_name_token) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(ast_verifier, token_get_name(func_name_token));
    if (node_func) {
        AST_VERIFIER_ERROR(func_name_token, "function is already defined");
    }
}

static void ast_verifier_verify_func_params(ast_verifier *ast_verifier, list *params) {
    ast_verifier_reset_vars_list(ast_verifier);
    long offset = sizeof(size_t) * (1 + list_get_size(params));
    LIST_FOR_EACH(ast_node_var, var, params) {
        ast_verifier_verify_var_name_is_new(ast_verifier, ast_node_var_get_token(var));
        ast_node_var_set_offset(var, offset);
        offset -= sizeof(size_t);
        ast_verifier_add_var(ast_verifier, var);
    }
}

void ast_verifier_verify_func(ast_verifier *ast_verifier, ast_node_func *node_func) {
    ast_verifier_verify_func_name_is_new(ast_verifier, ast_node_func_get_name_token(node_func));
    ast_verifier_add_func(ast_verifier, node_func);

    if (string_view_compare_with_ctr(token_get_name(ast_node_func_get_name_token(node_func)), "enter")) {
        ast_verifier_set_enter_exists(ast_verifier);
    }

    ast_verifier_verify_func_params(ast_verifier, ast_node_func_get_params(node_func));
    ast_verifier_verify_scope(ast_verifier, ast_node_func_get_scope(node_func));
}