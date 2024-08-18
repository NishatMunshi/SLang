#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_VAR_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_VAR_H

#include "ds/ast/nodes/var.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_var(ast_verifier *ast_verifier, ast_node_var *node_var);

#endif // SLC_MODULES_AST_VERIFIER_AST_NODES_VAR_H