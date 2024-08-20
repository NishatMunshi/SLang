#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_PAREN_EXPR_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_PAREN_EXPR_H

#include "ds/ast/nodes/paren_expr.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_paren_expr(ast_verifier *ast_verifier, ast_node_paren_expr *node_paren_expr);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_PAREN_EXPR_H