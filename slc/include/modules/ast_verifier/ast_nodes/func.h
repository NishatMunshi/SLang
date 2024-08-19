#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_FUNC_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_FUNC_H

#include "modules/ast_verifier/ast_verifier.h"
#include "ds/ast/nodes/func.h"

void ast_verifier_verify_func(ast_verifier *ast_verifier, ast_node_func *node_func);

#endif // SLC_MODULES_AST_VERIFIER_AST_NODES_FUNC_H