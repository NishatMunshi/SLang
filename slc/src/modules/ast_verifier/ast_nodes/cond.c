#include "modules/ast_verifier/ast_nodes/cond.h"

#include "modules/ast_verifier/ast_nodes/expr.h"
#include "modules/ast_verifier/ast_nodes/scope.h"

void ast_verifier_verify_cond(ast_verifier *ast_verifier, ast_node_cond *node_cond) {
    ast_verifier_verify_expr(ast_verifier, ast_node_cond_get_expr(node_cond));
    ast_verifier_verify_scope(ast_verifier, ast_node_cond_get_scope(node_cond));
}