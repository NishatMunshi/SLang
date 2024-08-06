#ifndef SLC_AST_NODE_H
#define SLC_AST_NODE_H

#include "list.h"
#include "string_view.h"
#include "token.h"

typedef struct ast_node_prog_struct ast_node_prog;
typedef struct ast_node_func_struct ast_node_func;
typedef struct ast_node_scope_struct ast_node_scope;
typedef struct ast_node_stmt_struct ast_node_stmt;
typedef struct ast_node_decl_struct ast_node_decl;
typedef struct ast_node_decl_struct ast_node_asst;
typedef struct ast_node_cond_struct ast_node_cond;
typedef struct ast_node_cond_struct ast_node_loop;
typedef struct ast_node_ret_struct ast_node_ret;
typedef struct ast_node_expr_struct ast_node_expr;
typedef struct ast_node_un_expr_struct ast_node_un_expr;
typedef struct ast_node_paren_expr_struct ast_node_paren_expr;
typedef struct ast_node_call_struct ast_node_call;
typedef struct ast_node_bin_expr_struct ast_node_bin_expr;
typedef struct ast_node_var_struct ast_node_var;
typedef struct ast_node_num_struct ast_node_num;

ast_node_prog *ast_node_prog_create(list *funcs);
list *         ast_node_prog_get_funcs(ast_node_prog *node_prog);

ast_node_func * ast_node_func_create(token *name, list *params, ast_node_scope *node_scope);
token *         ast_node_func_get_name_token(ast_node_func *node_func);
list *          ast_node_func_get_params(ast_node_func *node_func);
ast_node_scope *ast_node_func_get_scope(ast_node_func *node_func);

ast_node_scope *ast_node_scope_create();
list *          ast_node_scope_get_stmts(ast_node_scope *node_scope);
void            ast_node_scope_add_stmt(ast_node_scope *node_scope, ast_node_stmt *node_stmt);
void            ast_node_scope_set_num_local_vars(ast_node_scope *node_scope, size_t num);
size_t          ast_node_scope_get_num_local_vars(ast_node_scope *node_scope);

typedef enum ast_node_statement_type_enum {
    AST_NODE_STMT_DECL,
    AST_NODE_STMT_ASST,
    AST_NODE_STMT_COND,
    AST_NODE_STMT_LOOP,
    AST_NODE_STMT_RET,
} ast_node_stmt_type;

ast_node_stmt *    ast_node_stmt_create_decl(ast_node_decl *node_decl);
ast_node_stmt *    ast_node_stmt_create_asst(ast_node_asst *node_asst);
ast_node_stmt *    ast_node_stmt_create_cond(ast_node_cond *node_cond);
ast_node_stmt *    ast_node_stmt_create_loop(ast_node_loop *node_loop);
ast_node_stmt *    ast_node_stmt_create_ret(ast_node_ret *node_ret);
ast_node_stmt_type ast_node_stmt_get_type(ast_node_stmt *node_stmt);
ast_node_decl *    ast_node_stmt_get_decl(ast_node_stmt *node_stmt);
ast_node_asst *    ast_node_stmt_get_asst(ast_node_stmt *node_stmt);
ast_node_cond *    ast_node_stmt_get_cond(ast_node_stmt *node_stmt);
#define            ast_node_stmt_get_loop ast_node_stmt_get_cond
ast_node_ret *     ast_node_stmt_get_ret(ast_node_stmt *node_stmt);

ast_node_decl *ast_node_decl_create(ast_node_var *node_var, ast_node_expr *node_expr);
ast_node_var * ast_node_decl_get_var(ast_node_decl *node_decl);
ast_node_expr *ast_node_decl_get_rhs(ast_node_decl *node_decl);

#define ast_node_asst_create ast_node_decl_create
#define ast_node_asst_get_var ast_node_decl_get_var
#define ast_node_asst_get_rhs ast_node_decl_get_rhs

ast_node_cond * ast_node_cond_create(ast_node_expr *node_expr, ast_node_scope *node_scope);
ast_node_expr * ast_node_cond_get_expr(ast_node_cond *node_cond);
ast_node_scope *ast_node_cond_get_scope(ast_node_cond *node_cond);

#define ast_node_loop_create ast_node_cond_create
#define ast_node_loop_get_expr ast_node_cond_get_expr
#define ast_node_loop_get_scope ast_node_cond_get_scope

ast_node_ret * ast_node_ret_create(ast_node_expr *node_expr);
ast_node_expr *ast_node_ret_get_expr(ast_node_ret *node_ret);

typedef enum ast_node_expr_type_enum {
    AST_NODE_EXPR_UN_EXPR,
    AST_NODE_EXPR_BIN_EXPR
} ast_node_expr_type;

ast_node_expr *    ast_node_expr_create_un_expr(ast_node_un_expr *node_un_expr);
ast_node_expr *    ast_node_expr_create_bin_expr(ast_node_bin_expr *node_bin_expr);
ast_node_expr_type ast_node_expr_get_type(ast_node_expr *node_expr);
ast_node_un_expr * ast_node_expr_get_un_expr(ast_node_expr *node_expr);
ast_node_bin_expr *ast_node_expr_get_bin_expr(ast_node_expr *node_expr);

typedef enum ast_node_un_expr_type_enum {
    AST_NODE_UN_EXPR_NUM,
    AST_NODE_UN_EXPR_VAR,
    AST_NODE_UN_EXPR_PAREN_EXPR,
    AST_NODE_UN_EXPR_CALL,
} ast_node_un_expr_type;

ast_node_un_expr *    ast_node_un_expr_create_num(ast_node_num *node_num);
ast_node_un_expr *    ast_node_un_expr_create_var(ast_node_var *node_var);
ast_node_un_expr *    ast_node_un_expr_create_paren_expr(ast_node_paren_expr *node_paren_expr);
ast_node_un_expr *    ast_node_un_expr_create_call(ast_node_call *node_call);
ast_node_un_expr_type ast_node_un_expr_get_type(ast_node_un_expr *node_un_expr);
ast_node_num *        ast_node_un_expr_get_num(ast_node_un_expr *node_un_expr);
ast_node_var *        ast_node_un_expr_get_var(ast_node_un_expr *node_un_expr);
ast_node_paren_expr * ast_node_un_expr_get_paren_expr(ast_node_un_expr *node_un_expr);
ast_node_call *       ast_node_un_expr_get_call(ast_node_un_expr *node_un_expr);

ast_node_num *ast_node_num_create(string_view *num_value);
string_view * ast_node_num_get_value(ast_node_num *node_num);

ast_node_var *ast_node_var_create(token *var_name_token);
string_view * ast_node_var_get_name(ast_node_var *node_var);
void          ast_node_var_set_offset(ast_node_var *node_var, long offset);
long          ast_node_var_get_offset(ast_node_var *node_var);
token *       ast_node_var_get_token(ast_node_var *node_var);

ast_node_paren_expr *ast_node_paren_expr_create(ast_node_expr *node_expr);
ast_node_expr *      ast_node_paren_expr_get_expr(ast_node_paren_expr *node_paren_expr);

ast_node_call *ast_node_call_create(token *name, list *args);
token *        ast_node_call_get_name(ast_node_call *node_call);
list *         ast_node_call_get_args(ast_node_call *node_call);

typedef enum ast_node_bin_expr_type_enum {
    AST_NODE_BIN_EXPR_ADD,
    AST_NODE_BIN_EXPR_SUB,
} ast_node_bin_expr_type;

ast_node_bin_expr *    ast_node_bin_expr_create_add(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr *    ast_node_bin_expr_create_sub(ast_node_expr *node_expr_left, ast_node_un_expr *node_expr_un_right);
void                   ast_node_bin_expr_add_right(ast_node_bin_expr *node_bin_expr, ast_node_un_expr *node_expr_un_right);
ast_node_bin_expr_type ast_node_bin_expr_get_type(ast_node_bin_expr *node_bin_expr);
ast_node_expr *        ast_node_bin_expr_get_left(ast_node_bin_expr *node_bin_expr);
ast_node_un_expr *     ast_node_bin_expr_get_right(ast_node_bin_expr *node_bin_expr);

#endif // SLC_AST_NODE_H