#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_EXPR_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_EXPR_H

#include "ds/ast/nodes/expr.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_expr(ast_verifier *ast_verifier, ast_node_expr *node_expr);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_EXPR_H
