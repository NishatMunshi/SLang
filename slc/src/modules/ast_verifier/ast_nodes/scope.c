#include "modules/ast_verifier/ast_nodes/scope.h"

#include "modules/ast_verifier/ast_nodes/stmt.h"

void ast_verifier_verify_scope(ast_verifier *ast_verifier, ast_node_scope *node_scope) {
    list *stmts = ast_node_scope_get_stmts(node_scope);
    size_t num_vars_higher_scope = ast_verifier_get_num_vars(ast_verifier);

    ast_verifier_enter_scope(ast_verifier);

    LIST_FOR_EACH(ast_node_stmt, stmt, stmts) {
        ast_verifier_verify_stmt(ast_verifier, stmt);
    }
    size_t num_local_vars = ast_verifier_get_num_vars(ast_verifier) - num_vars_higher_scope;
    ast_node_scope_set_num_local_vars(node_scope, num_local_vars);

    ast_verifier_leave_scope(ast_verifier);
}