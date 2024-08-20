#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_BIN_EXPR_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_BIN_EXPR_H

#include "ds/ast/nodes/bin_expr.h"
#include "modules/ast_verifier/ast_verifier.h"

void ast_verifier_verify_bin_expr(ast_verifier *ast_verifier, ast_node_bin_expr *node_bin_expr);

#endif  // SLC_MODULES_AST_VERIFIER_AST_NODES_BIN_EXPR_H