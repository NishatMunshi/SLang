#include "modules/ast_verifier/ast_nodes/ret.h"

#include "modules/ast_verifier/ast_nodes/expr.h"

void ast_verifier_verify_ret(ast_verifier *ast_verifier, ast_node_ret *node_ret) {
    ast_verifier_verify_expr(ast_verifier, ast_node_ret_get_expr(node_ret));
}