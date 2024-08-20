#ifndef SLC_MODULES_AST_VERIFIER_AST_VERIFIER_H
#define SLC_MODULES_AST_VERIFIER_AST_VERIFIER_H

#include <stdio.h>
#include <stdlib.h>

#include "ds/ast/nodes/func.h"
#include "ds/ast/nodes/var.h"
#include "ds/list/list.h"
#include "ds/stack/stack.h"
#include "ds/token/token.h"

typedef struct ast_verifier_struct ast_verifier;

ast_verifier *ast_verifier_create();

#define AST_VERIFIER_ERROR(TOKEN, MESSAGE)    \
    printf("[SLC]: [AST_VERIFIER ERROR]: ");  \
    token_print_pos(TOKEN);                   \
    printf(MESSAGE ": ");                     \
    string_view_print(token_get_name(TOKEN)); \
    printf("\n");                             \
    exit(1);

bool ast_verifier_enter_exists(ast_verifier *ast_verifier);
ast_node_var *ast_verifier_verify_var_exists(ast_verifier *ast_verifier, token *var_name_token);
ast_node_var *ast_verifier_vars_stack_contains_var(ast_verifier *ast_verifier, string_view *var_name);
void ast_verifier_add_var(ast_verifier *ast_verifier, ast_node_var *node_var);
ast_node_var *ast_verifer_get_last_var(ast_verifier *ast_verifier);
size_t ast_verifier_get_num_vars(ast_verifier *ast_verifier);
void ast_verifier_enter_scope(ast_verifier *ast_verifier);
void ast_verifier_leave_scope(ast_verifier *ast_verifier);
ast_node_func *ast_verifier_funcs_list_contains_func(ast_verifier *ast_verifier, string_view *func_name);
void ast_verifier_set_enter_exists(ast_verifier *ast_verifier);
void ast_verifier_verify_var_name_is_new(ast_verifier *ast_verifier, token *var_name_token);
void ast_verifier_reset_vars_list(ast_verifier *ast_verifier);
void ast_verifier_add_func(ast_verifier *ast_verifier, ast_node_func *node_func);

#endif  // SLC_MODULES_AST_VERIFIER_AST_VERIFIER_H