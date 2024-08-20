#ifndef SLC_DS_AST_NODES_FUNC_H
#define SLC_DS_AST_NODES_FUNC_H

#include "ds/ast/nodes/scope.h"
#include "ds/list/list.h"
#include "ds/token/token.h"

typedef struct ast_node_func_struct ast_node_func;

ast_node_func *ast_node_func_create(token *name, list *params, ast_node_scope *node_scope);

token *ast_node_func_get_name_token(ast_node_func *node_func);
list *ast_node_func_get_params(ast_node_func *node_func);
ast_node_scope *ast_node_func_get_scope(ast_node_func *node_func);

#endif  // SLC_DS_AST_NODES_FUNC_H
