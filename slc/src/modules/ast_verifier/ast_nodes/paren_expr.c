#include "modules/ast_verifier/ast_nodes/paren_expr.h"

#include "modules/ast_verifier/ast_nodes/expr.h"

void ast_verifier_verify_paren_expr(ast_verifier *ast_verifier, ast_node_paren_expr *node_paren_expr) {
    ast_verifier_verify_expr(ast_verifier, ast_node_paren_expr_get_expr(node_paren_expr));
}
