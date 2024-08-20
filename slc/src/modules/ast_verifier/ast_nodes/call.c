#include "modules/ast_verifier/ast_nodes/call.h"

#include "ds/ast/nodes/func.h"
#include "modules/ast_verifier/ast_nodes/expr.h"

static ast_node_func *ast_verifier_verify_func_exists(ast_verifier *ast_verifier, token *func_name_token) {
    ast_node_func *node_func = ast_verifier_funcs_list_contains_func(ast_verifier, token_get_name(func_name_token));
    if (node_func) {
        return node_func;
    }
    AST_VERIFIER_ERROR(func_name_token, "function is not defined");
}

static void ast_verifier_check_num_args(ast_node_call *node_call, ast_node_func *node_func) {
    if (list_get_size(ast_node_func_get_params(node_func)) != list_get_size(ast_node_call_get_args(node_call))) {
        AST_VERIFIER_ERROR(ast_node_call_get_name(node_call), "incorrect number of arguments in function call");
    }
}

void ast_verifier_verify_call(ast_verifier *ast_verifier, ast_node_call *node_call) {
    ast_node_func *node_func = ast_verifier_verify_func_exists(ast_verifier, ast_node_call_get_name(node_call));
    ast_verifier_check_num_args(node_call, node_func);
    LIST_FOR_EACH(ast_node_expr, expr, ast_node_call_get_args(node_call)) {
        ast_verifier_verify_expr(ast_verifier, expr);
    }
}