#ifndef SLC_AST_NODE_VAR_H
#define SLC_AST_NODE_VAR_H

#include "ds/token/token.h"

typedef struct ast_node_var_struct ast_node_var;

ast_node_var *ast_node_var_create(token *var_name_token);

void ast_node_var_set_offset(ast_node_var *node_var, long offset);

string_view * ast_node_var_get_name(ast_node_var *node_var);
long          ast_node_var_get_offset(ast_node_var *node_var);
token *       ast_node_var_get_token(ast_node_var *node_var);


#endif // SLC_AST_NODE_VAR_H