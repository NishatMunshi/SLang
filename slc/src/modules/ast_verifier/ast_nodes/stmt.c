#include "modules/ast_verifier/ast_nodes/stmt.h"

#include "modules/ast_verifier/ast_nodes/asst.h"
#include "modules/ast_verifier/ast_nodes/cond.h"
#include "modules/ast_verifier/ast_nodes/decl.h"
#include "modules/ast_verifier/ast_nodes/expr.h"
#include "modules/ast_verifier/ast_nodes/loop.h"
#include "modules/ast_verifier/ast_nodes/ret.h"
#include "utils/utils.h"

void ast_verifier_verify_stmt(ast_verifier *ast_verifier, ast_node_stmt *node_stmt) {
    switch (ast_node_stmt_get_type(node_stmt)) {
        case AST_NODE_STMT_DECL:
            ast_verifier_verify_decl(ast_verifier, ast_node_stmt_get_decl(node_stmt));
            break;
        case AST_NODE_STMT_ASST:
            ast_verifier_verify_asst(ast_verifier, ast_node_stmt_get_asst(node_stmt));
            break;
        case AST_NODE_STMT_COND:
            ast_verifier_verify_cond(ast_verifier, ast_node_stmt_get_cond(node_stmt));
            break;
        case AST_NODE_STMT_LOOP:
            ast_verifier_verify_loop(ast_verifier, ast_node_stmt_get_loop(node_stmt));
            break;
        case AST_NODE_STMT_RET:
            ast_verifier_verify_expr(ast_verifier, ast_node_ret_get_expr(ast_node_stmt_get_ret(node_stmt)));
            break;

        default:
            UNREACHABLE();
    }
}