#ifndef SLC_AST_NODE_UN_EXPR_H
#define SLC_AST_NODE_UN_EXPR_H

#include "ds/ast/ast_node_num.h"
#include "ds/ast/ast_node_var.h"
#include "ds/ast/ast_node_paren_expr.h"
#include "ds/ast/ast_node_call.h"

typedef struct ast_node_un_expr_struct ast_node_un_expr;
typedef struct ast_node_paren_expr_struct ast_node_paren_expr;
typedef struct ast_node_expr_struct ast_node_expr;

typedef enum ast_node_un_expr_type_enum {
    AST_NODE_UN_EXPR_NUM,
    AST_NODE_UN_EXPR_VAR,
    AST_NODE_UN_EXPR_PAREN_EXPR,
    AST_NODE_UN_EXPR_CALL,
} ast_node_un_expr_type;

ast_node_un_expr *ast_node_un_expr_create_num(ast_node_num *node_num);
ast_node_un_expr *ast_node_un_expr_create_var(ast_node_var *node_var);
ast_node_un_expr *ast_node_un_expr_create_paren_expr(ast_node_paren_expr *node_paren_expr);
ast_node_un_expr *ast_node_un_expr_create_call(ast_node_call *node_call);

ast_node_un_expr_type ast_node_un_expr_get_type(ast_node_un_expr *node_un_expr);
ast_node_num *        ast_node_un_expr_get_num(ast_node_un_expr *node_un_expr);
ast_node_var *        ast_node_un_expr_get_var(ast_node_un_expr *node_un_expr);
ast_node_paren_expr * ast_node_un_expr_get_paren_expr(ast_node_un_expr *node_un_expr);
ast_node_call *       ast_node_un_expr_get_call(ast_node_un_expr *node_un_expr);

#endif // SLC_AST_NODE_UN_EXPR_H