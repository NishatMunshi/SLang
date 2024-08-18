#ifndef SLC_DS_AST_NODES_SCOPE_H
#define SLC_DS_AST_NODES_SCOPE_H

#include "ds/list/list.h"
#include "ds/ast/nodes/stmt.h"

typedef struct ast_node_scope_struct ast_node_scope;
typedef struct ast_node_stmt_struct ast_node_stmt;

ast_node_scope *ast_node_scope_create();

void ast_node_scope_add_stmt(ast_node_scope *node_scope, ast_node_stmt *node_stmt);

list * ast_node_scope_get_stmts(ast_node_scope *node_scope);
void   ast_node_scope_set_num_local_vars(ast_node_scope *node_scope, size_t num);
size_t ast_node_scope_get_num_local_vars(ast_node_scope *node_scope);

#endif // SLC_DS_AST_NODES_SCOPE_H