#include "modules/ast_verifier/ast_nodes/bin_expr.h"

#include "modules/ast_verifier/ast_nodes/expr.h"
#include "modules/ast_verifier/ast_nodes/un_expr.h"

void ast_verifier_verify_bin_expr(ast_verifier *ast_verifier, ast_node_bin_expr *node_bin_expr) {
    ast_verifier_verify_expr(ast_verifier, ast_node_bin_expr_get_left(node_bin_expr));
    ast_verifier_verify_un_expr(ast_verifier, ast_node_bin_expr_get_right(node_bin_expr));
}