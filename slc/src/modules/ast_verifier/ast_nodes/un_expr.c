#include "modules/ast_verifier/ast_nodes/un_expr.h"
#include "modules/ast_verifier/ast_nodes/call.h"
#include "modules/ast_verifier/ast_nodes/expr.h"
#include "utils/utils.h"

void ast_verifier_verify_un_expr(ast_verifier *ast_verifier, ast_node_un_expr *node_un_expr) {
    switch (ast_node_un_expr_get_type(node_un_expr)) {
    case AST_NODE_UN_EXPR_NUM: break;
    case AST_NODE_UN_EXPR_VAR: {
        ast_node_var *node_var = ast_node_un_expr_get_var(node_un_expr);
        ast_node_var *list_var = ast_verifier_verify_var_exists(ast_verifier, ast_node_var_get_token(node_var));
        ast_node_var_set_offset(node_var, ast_node_var_get_offset(list_var));
        }
        break;
    case AST_NODE_UN_EXPR_PAREN_EXPR: ast_verifier_verify_expr(ast_verifier, ast_node_paren_expr_get_expr(ast_node_un_expr_get_paren_expr(node_un_expr))); break;
    case AST_NODE_UN_EXPR_CALL: ast_verifier_verify_call(ast_verifier, ast_node_un_expr_get_call(node_un_expr)); break;

    default: UNREACHABLE();
    }
}
