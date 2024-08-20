#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_SCOPE_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_SCOPE_H

#include "ds/ast/nodes/scope.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_scope(ast_verifier *ast_verifier, ast_node_scope *node_scope);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_SCOPE_H