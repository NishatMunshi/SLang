#include "modules/ast_verifier/ast_nodes/var.h"

void ast_verifier_verify_var(ast_verifier *ast_verifier, ast_node_var *node_var) {
    ast_verifier_verify_var_exists(ast_verifier, ast_node_var_get_token(node_var));
}