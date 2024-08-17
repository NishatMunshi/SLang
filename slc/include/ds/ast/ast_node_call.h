#ifndef SLC_AST_NODE_CALL_H
#define SLC_AST_NODE_CALL_H

#include "ds/token/token.h"
#include "ds/list/list.h"

typedef struct ast_node_call_struct ast_node_call;

ast_node_call *ast_node_call_create(token *name, list *args);

token *ast_node_call_get_name(ast_node_call *node_call);
list * ast_node_call_get_args(ast_node_call *node_call);

#endif // SLC_AST_NODE_CALL_H