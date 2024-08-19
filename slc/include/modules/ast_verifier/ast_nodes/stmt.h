#ifndef SLC_MODULES_AST_VERIFIER_AST_NODES_STMT_H
#define SLC_MODULES_AST_VERIFIER_AST_NODES_STMT_H

#include "modules/ast_verifier/ast_verifier.h"
#include "ds/ast/nodes/stmt.h"

void ast_verifier_verify_stmt(ast_verifier *ast_verifier, ast_node_stmt *node_stmt);

#endif // SLC_MODULES_AST_VERIFIER_AST_NODES_STMT_H