#ifndef SLC_DS_AST_NODES_LOOP_H
#define SLC_DS_AST_NODES_LOOP_H

typedef struct ast_node_cond_struct ast_node_loop;

#define ast_node_loop_create ast_node_cond_create

#define ast_node_loop_get_expr ast_node_cond_get_expr
#define ast_node_loop_get_scope ast_node_cond_get_scope

#endif // SLC_DS_AST_NODES_LOOP_H