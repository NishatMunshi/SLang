#include "modules/ast_verifier/ast_nodes/asst.h"
#include "modules/ast_verifier/ast_nodes/expr.h"

void ast_verifier_verify_asst(ast_verifier *ast_verifier, ast_node_asst *node_asst) {
    ast_node_var *node_var = ast_node_asst_get_var(node_asst);
    ast_verifier_verify_var_exists(ast_verifier, ast_node_var_get_token(node_var));
    ast_verifier_verify_expr(ast_verifier, ast_node_asst_get_rhs(node_asst));
}