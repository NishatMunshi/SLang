#include "modules/ast_verifier/ast_nodes/expr.h"
#include "modules/ast_verifier/ast_nodes/un_expr.h"
#include "modules/ast_verifier/ast_nodes/bin_expr.h"
#include "utils/utils.h"

void ast_verifier_verify_expr(ast_verifier * ast_verifier,ast_node_expr *node_expr) {
    switch (ast_node_expr_get_type(node_expr)) {
    case AST_NODE_EXPR_UN_EXPR: ast_verifier_verify_un_expr(ast_verifier, ast_node_expr_get_un_expr(node_expr)); break;
    case AST_NODE_EXPR_BIN_EXPR: ast_verifier_verify_bin_expr(ast_verifier, ast_node_expr_get_bin_expr(node_expr)); break;

    default: UNREACHABLE();
    }
}