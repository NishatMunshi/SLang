#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_RET_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_RET_H

#include "ds/ast/nodes/ret.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_ret(ast_verifier *ast_verifier, ast_node_ret *node_ret);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_RET_H