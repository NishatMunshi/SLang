#include "modules/ast_verifier/ast_nodes/decl.h"
#include "modules/ast_verifier/ast_nodes/expr.h"

static long ast_verifier_calc_new_var_offset(ast_verifier *ast_verifier) {
    ast_node_var *last_node_var = ast_verifer_get_last_var(ast_verifier);
    long offset = 0;
    if (last_node_var) {
        offset = ast_node_var_get_offset(last_node_var);
    }
    return (offset >= 0) ? -sizeof(size_t) : (offset - sizeof(size_t));
}

void ast_verifier_verify_decl(ast_verifier *ast_verifier, ast_node_decl *node_decl) {
    ast_node_var *node_var = ast_node_decl_get_var(node_decl);
    ast_verifier_verify_var_name_is_new(ast_verifier, ast_node_var_get_token(node_var));
    ast_verifier_verify_expr(ast_verifier, ast_node_decl_get_rhs(node_decl));
    ast_node_var_set_offset(node_var, ast_verifier_calc_new_var_offset(ast_verifier));
    ast_verifier_add_var(ast_verifier, node_var);
}
