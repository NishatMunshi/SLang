#ifndef SLC_DS_AST_NODES_STMT_H
#define SLC_DS_AST_NODES_STMT_H

#include "ds/ast/nodes/asst.h"
#include "ds/ast/nodes/cond.h"
#include "ds/ast/nodes/decl.h"
#include "ds/ast/nodes/loop.h"
#include "ds/ast/nodes/ret.h"

typedef struct ast_node_stmt_struct ast_node_stmt;
typedef struct ast_node_cond_struct ast_node_cond;

typedef enum ast_node_statement_type_enum {
    AST_NODE_STMT_DECL,
    AST_NODE_STMT_ASST,
    AST_NODE_STMT_COND,
    AST_NODE_STMT_LOOP,
    AST_NODE_STMT_RET,
} ast_node_stmt_type;

ast_node_stmt *ast_node_stmt_create_decl(ast_node_decl *node_decl);
ast_node_stmt *ast_node_stmt_create_asst(ast_node_asst *node_asst);
ast_node_stmt *ast_node_stmt_create_cond(ast_node_cond *node_cond);
ast_node_stmt *ast_node_stmt_create_loop(ast_node_loop *node_loop);
ast_node_stmt *ast_node_stmt_create_ret(ast_node_ret *node_ret);

ast_node_stmt_type ast_node_stmt_get_type(ast_node_stmt *node_stmt);
ast_node_decl *ast_node_stmt_get_decl(ast_node_stmt *node_stmt);
ast_node_asst *ast_node_stmt_get_asst(ast_node_stmt *node_stmt);
ast_node_cond *ast_node_stmt_get_cond(ast_node_stmt *node_stmt);
#define ast_node_stmt_get_loop ast_node_stmt_get_cond
ast_node_ret *ast_node_stmt_get_ret(ast_node_stmt *node_stmt);

#endif  // SLC_DS_AST_NODES_STMT_H