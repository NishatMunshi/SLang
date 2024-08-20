#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_COND_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_COND_H

#include "ds/ast/nodes/cond.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_cond(ast_verifier *ast_verifier, ast_node_cond *node_cond);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_COND_H