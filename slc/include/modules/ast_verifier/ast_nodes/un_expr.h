#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_UN_EXPR_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_UN_EXPR_H

#include "modules/ast_verifier/ast_verifier.h"
#include "ds/ast/nodes/un_expr.h"

void ast_verifier_verify_un_expr(ast_verifier *ast_verifier, ast_node_un_expr *node_un_expr);

#endif // SLC_MODULES_AST_VERIFIER_AST_NODES_UN_EXPR_H