#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_DECL_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_DECL_H

#include "ds/ast/nodes/decl.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_decl(ast_verifier *ast_verifier, ast_node_decl *node_decl);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_DECL_H
