#include "modules/ast_verifier/ast_verifier.h"
#include "modules/ast_verifier/ast_nodes/prog.h"
#include "modules/ast_verifier/ast_nodes/func.h"

static void ast_verifier_verify_enter_exists(ast_verifier *ast_verifier) {
    if (!ast_verifier_enter_exists(ast_verifier)) {
        printf("[SLC]: [AST_VERIFIER ERROR]: function \"enter\" not found.\n");
        exit(1);
    }
}

void ast_verifier_verify_prog(ast_node_prog *node_prog) {
    ast_verifier *ast_verifier = ast_verifier_create();

    LIST_FOR_EACH(ast_node_func, func, ast_node_prog_get_funcs(node_prog)) {
        ast_verifier_verify_func(ast_verifier, func);
    }

    ast_verifier_verify_enter_exists(ast_verifier);
}