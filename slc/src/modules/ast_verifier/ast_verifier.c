#include "modules/ast_verifier/ast_verifier.h"

#include "ds/stack/stack.h"
#include "memory/arena_allocator.h"

struct ast_verifier_struct {
    list *funcs_list;
    stack *vars_stack;
    bool enter_exists;
    size_t var_stack_size_at_scope_entry;
};

ast_verifier *ast_verifier_create() {
    ast_verifier *ast_verifier = arena_allocator_allocate(sizeof(struct ast_verifier_struct));
    ast_verifier->funcs_list = list_create();
    ast_verifier->vars_stack = stack_create();
    ast_verifier->enter_exists = false;
    ast_verifier->var_stack_size_at_scope_entry = 0;

    return ast_verifier;
}

bool ast_verifier_enter_exists(ast_verifier *ast_verifier) {
    return ast_verifier->enter_exists;
}

ast_node_var *ast_verifier_vars_stack_contains_var(ast_verifier *ast_verifier, string_view *var_name) {
    STACK_FOR_EACH(ast_node_var, var, ast_verifier->vars_stack) {
        if (string_view_compare(ast_node_var_get_name(var), var_name)) {
            return var;
        }
    }
    return NULL;
}

ast_node_var *ast_verifier_verify_var_exists(ast_verifier *ast_verifier, token *var_name_token) {
    ast_node_var *list_var = ast_verifier_vars_stack_contains_var(ast_verifier, token_get_name(var_name_token));
    if (list_var) {
        return list_var;
    }
    AST_VERIFIER_ERROR(var_name_token, "variable is not defined");
}

void ast_verifier_add_var(ast_verifier *ast_verifier, ast_node_var *node_var) {
    stack_push(ast_verifier->vars_stack, node_var);
}

ast_node_var *ast_verifer_get_last_var(ast_verifier *ast_verifier) {
    return stack_node_get_data(stack_get_top(ast_verifier->vars_stack));
}

size_t ast_verifier_get_num_vars(ast_verifier *ast_verifier) {
    return stack_get_size(ast_verifier->vars_stack);
}

void ast_verifier_enter_scope(ast_verifier *ast_verifier) {
    ast_verifier->var_stack_size_at_scope_entry = ast_verifier_get_num_vars(ast_verifier);
}

void ast_verifier_leave_scope(ast_verifier *ast_verifier) {
    size_t vars_stack_current_size = stack_get_size(ast_verifier->vars_stack);
    size_t items_to_pop = vars_stack_current_size - ast_verifier->var_stack_size_at_scope_entry;
    for (size_t i = 0; i < items_to_pop; ++i) {
        stack_pop(ast_verifier->vars_stack);
    }
}

ast_node_func *ast_verifier_funcs_list_contains_func(ast_verifier *ast_verifier, string_view *func_name) {
    LIST_FOR_EACH(ast_node_func, func, ast_verifier->funcs_list) {
        if (string_view_compare(token_get_name(ast_node_func_get_name_token(func)), func_name)) {
            return func;
        }
    }
    return NULL;
}

void ast_verifier_set_enter_exists(ast_verifier *ast_verifier) {
    ast_verifier->enter_exists = true;
}

void ast_verifier_verify_var_name_is_new(ast_verifier *ast_verifier, token *var_name_token) {
    if (ast_verifier_vars_stack_contains_var(ast_verifier, token_get_name(var_name_token))) {
        AST_VERIFIER_ERROR(var_name_token, "variable is already defined");
    }
}

void ast_verifier_reset_vars_list(ast_verifier *ast_verifier) {
    ast_verifier->vars_stack = stack_create();
}

void ast_verifier_add_func(ast_verifier *ast_verifier, ast_node_func *node_func) {
    list_push(ast_verifier->funcs_list, node_func);
}