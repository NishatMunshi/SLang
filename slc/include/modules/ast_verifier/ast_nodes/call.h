#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_CALL_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_CALL_H

#include "modules/ast_verifier/ast_verifier.h"
#include "ds/ast/nodes/call.h"

void ast_verifier_verify_call(ast_verifier *ast_verifier, ast_node_call *node_call);

#endif // SLC_MODULES_AST_VERIFIER_AST_NODES_CALL_H