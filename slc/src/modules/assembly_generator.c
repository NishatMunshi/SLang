#include "modules/assembly_generator.h"
#include "memory/arena_allocator.h"
#include "ds/list/list.h"
#include "utils/utils.h"
#include "ds/ast/nodes/num.h"
#include "ds/ast/nodes/var.h"
#include "ds/ast/nodes/expr.h"
#include "ds/ast/nodes/decl.h"
#include "ds/ast/nodes/asst.h"
#include "ds/ast/nodes/scope.h"
#include "ds/ast/nodes/func.h"

#include <stdio.h>
#include <string.h>

static string *ass_gen_generate_num(ast_node_num *node_num) {
    string *ass_reg = string_create_from_cstr("    mov rax, ");
    string *ass_num = string_create_from_string_view(ast_node_num_get_value(node_num));

    string_concat(ass_reg, ass_num);
    string_concat(ass_num, string_create_from_cstr("\n"));

    return ass_reg;
}

static string *ass_gen_generate_var(ast_node_var *node_var) {
    string *ass_reg = string_create_from_cstr("    mov rax, ");
    string *ass_var = string_create_from_cstr("[rbp + (");
    string *ass_offset = string_create_from_num(ast_node_var_get_offset(node_var));
    string *ass_square_bracket = string_create_from_cstr(")]\n");

    string_concat(ass_reg, ass_var);
    string_concat(ass_var, ass_offset);
    string_concat(ass_offset, ass_square_bracket);

    return ass_reg;
}

static string *ass_gen_generate_expr(ast_node_expr *node_expr);
static string *ass_gen_generate_un_expr(ast_node_un_expr *node_un_expr);

static string *ass_gen_generate_bin_expr(ast_node_bin_expr *node_bin_expr) {
    string *ass_left_expr = ass_gen_generate_expr(ast_node_bin_expr_get_left(node_bin_expr));
    string *ass_save_rax = string_create_from_cstr("    push rax\n");
    string *ass_right_expr = ass_gen_generate_un_expr(ast_node_bin_expr_get_right(node_bin_expr));
    string *ass_load_saved_rax = string_create_from_cstr("    mov rbx, rax\n"
                                                         "    pop rax\n");
    string *ass_instruction = NULL;
    switch (ast_node_bin_expr_get_type(node_bin_expr)) {
    case AST_NODE_BIN_EXPR_ADD: ass_instruction = string_create_from_cstr("    add rax, rbx\n"); break;
    case AST_NODE_BIN_EXPR_SUB: ass_instruction = string_create_from_cstr("    sub rax, rbx\n"); break;

    default: UNREACHABLE();
    }

    string_concat(ass_left_expr, ass_save_rax);
    string_concat(ass_save_rax, ass_right_expr);
    string_concat(ass_right_expr, ass_load_saved_rax);
    string_concat(ass_load_saved_rax, ass_instruction);

    return ass_left_expr;
}

static string *ass_gen_generate_paren_expr(ast_node_paren_expr *node_paren_expr) {
    return ass_gen_generate_expr(ast_node_paren_expr_get_expr(node_paren_expr));
}

static string *ass_gen_generate_call(ast_node_call *node_call) {
    string *ass_call = string_create_from_cstr("");
    LIST_FOR_EACH(ast_node_expr, expr, ast_node_call_get_args(node_call)) {
        string *ass_expr = ass_gen_generate_expr(expr);
        string *ass_create_arg = string_create_from_cstr("    push rax\n");
        string_concat(ass_call, ass_expr);
        string_concat(ass_expr, ass_create_arg);
    }

    string *ass_inst = string_create_from_cstr("    call ");
    string *ass_func_name = string_create_from_string_view(token_get_name(ast_node_call_get_name(node_call)));
    string *ass_clean_args = string_create_from_cstr("    add rsp, ");
    string *ass_num_args = string_create_from_num(sizeof(size_t) * list_get_size(ast_node_call_get_args(node_call)));

    string_concat(ass_call, ass_inst);
    string_concat(ass_inst, ass_func_name);
    string_concat(ass_func_name, string_create_from_cstr("\n"));
    string_concat(ass_func_name, ass_clean_args);
    string_concat(ass_clean_args, ass_num_args);
    string_concat(ass_num_args, string_create_from_cstr("\n"));

    return ass_call;
}

static string *ass_gen_generate_un_expr(ast_node_un_expr *node_un_expr) {
    switch (ast_node_un_expr_get_type(node_un_expr)) {
    case AST_NODE_UN_EXPR_NUM: return ass_gen_generate_num(ast_node_un_expr_get_num(node_un_expr));
    case AST_NODE_UN_EXPR_VAR: return ass_gen_generate_var(ast_node_un_expr_get_var(node_un_expr));
    case AST_NODE_UN_EXPR_PAREN_EXPR: return ass_gen_generate_paren_expr(ast_node_un_expr_get_paren_expr(node_un_expr));
    case AST_NODE_UN_EXPR_CALL: return ass_gen_generate_call(ast_node_un_expr_get_call(node_un_expr));

    default: UNREACHABLE();
    }
}

static string *ass_gen_generate_expr(ast_node_expr *node_expr) {
    switch (ast_node_expr_get_type(node_expr)) {
    case AST_NODE_EXPR_UN_EXPR: return ass_gen_generate_un_expr(ast_node_expr_get_un_expr(node_expr));
    case AST_NODE_EXPR_BIN_EXPR: return ass_gen_generate_bin_expr(ast_node_expr_get_bin_expr(node_expr));

    default: UNREACHABLE();
    }
}

static string *ass_gen_generate_decl(ast_node_decl *node_decl) {
    string *ass_expr = ass_gen_generate_expr(ast_node_decl_get_rhs(node_decl));
    string *ass_decl = string_create_from_cstr("    push rax    ; ");
    string *ass_var_name = string_create_from_string_view(ast_node_var_get_name(ast_node_decl_get_var(node_decl)));

    string_concat(ass_expr, ass_decl);
    string_concat(ass_decl, ass_var_name);
    string_concat(ass_var_name, string_create_from_cstr("\n"));

    return ass_expr;
}

static string *ass_gen_generate_asst(ast_node_asst *node_asst) {
    string *ass_expr = ass_gen_generate_expr(ast_node_asst_get_rhs(node_asst));
    string *ass_asst = string_create_from_cstr("    mov [rbp + (");
    string *ass_var = string_create_from_num(ast_node_var_get_offset(ast_node_asst_get_var(node_asst)));
    string *ass_reg = string_create_from_cstr(")], rax    ; ");
    string *ass_var_name = string_create_from_string_view(ast_node_var_get_name(ast_node_asst_get_var(node_asst)));

    string_concat(ass_expr, ass_asst);
    string_concat(ass_asst, ass_var);
    string_concat(ass_var, ass_reg);
    string_concat(ass_reg, ass_var_name);
    string_concat(ass_var_name, string_create_from_cstr("\n"));

    return ass_expr;
}

static string *ass_gen_generate_scope(ast_node_scope *node_scope);

static string *ass_gen_generate_new_label() {
    static size_t label = 0;
    char *template = "label%zu";
    char *cstr = arena_allocator_allocate(strlen(template) + utils_count_digits_in_num(label));
    sprintf(cstr, template, label++);
    string *ass_label = string_create_from_cstr(cstr);
    return ass_label;
}

static string *ass_gen_generate_cond(ast_node_cond *node_cond) {
    string *ass_expr = ass_gen_generate_expr(ast_node_cond_get_expr(node_cond));
    string *ass_test = string_create_from_cstr("    test rax, rax\n"
                                               "    jz ");
    string *ass_label1 = ass_gen_generate_new_label();
    string *ass_scope = ass_gen_generate_scope(ast_node_cond_get_scope(node_cond));
    string *ass_label2 = string_create_from_string(ass_label1);

    string_concat(ass_expr, ass_test);
    string_concat(ass_test, ass_label1);
    string_concat(ass_label1, string_create_from_cstr("\n"));
    string_concat(ass_label1, ass_scope);
    string_concat(ass_scope, ass_label2);
    string_concat(ass_label2, string_create_from_cstr(":\n"));

    return ass_expr;
}

static string *ass_gen_generate_loop(ast_node_loop *node_loop) {
    string *ass_loop_label = ass_gen_generate_new_label();
    string *ass_expr = ass_gen_generate_expr(ast_node_loop_get_expr(node_loop));
    string *ass_test = string_create_from_cstr("    test rax, rax\n"
                                               "    jz ");
    string *ass_skip_label = ass_gen_generate_new_label();
    string *ass_scope = ass_gen_generate_scope(ast_node_loop_get_scope(node_loop));
    string *ass_jump = string_create_from_cstr("    jmp ");
    string *ass_loop_label2 = string_create_from_string(ass_loop_label);
    string *ass_skip_label2 = string_create_from_string(ass_skip_label);

    string_concat(ass_loop_label, string_create_from_cstr(":\n"));
    string_concat(ass_loop_label, ass_expr);
    string_concat(ass_expr, ass_test);
    string_concat(ass_test, ass_skip_label);
    string_concat(ass_skip_label, string_create_from_cstr("\n"));
    string_concat(ass_skip_label, ass_scope);
    string_concat(ass_scope, ass_jump);
    string_concat(ass_jump, ass_loop_label2);
    string_concat(ass_loop_label2, string_create_from_cstr("\n"));
    string_concat(ass_loop_label2, ass_skip_label2);
    string_concat(ass_skip_label2, string_create_from_cstr(":\n"));

    return ass_loop_label;
}

static string *ass_gen_generate_ret(ast_node_ret *node_ret) {
    string *ass_expr = ass_gen_generate_expr(ast_node_ret_get_expr(node_ret));
    string *ass_ret = string_create_from_cstr("    mov rsp, rbp\n"
                                              "    pop rbp\n"
                                              "    ret\n");

    string_concat(ass_expr, ass_ret);
    return ass_expr;
}

static string *ass_gen_generate_stmt(ast_node_stmt *node_stmt) {
    switch (ast_node_stmt_get_type(node_stmt)) {
    case AST_NODE_STMT_DECL: return ass_gen_generate_decl(ast_node_stmt_get_decl(node_stmt));
    case AST_NODE_STMT_ASST: return ass_gen_generate_asst(ast_node_stmt_get_asst(node_stmt));
    case AST_NODE_STMT_COND: return ass_gen_generate_cond(ast_node_stmt_get_cond(node_stmt));
    case AST_NODE_STMT_LOOP: return ass_gen_generate_loop(ast_node_stmt_get_loop(node_stmt));
    case AST_NODE_STMT_RET: return ass_gen_generate_ret(ast_node_stmt_get_ret(node_stmt));

    default: UNREACHABLE();
    }
}

static string *ass_gen_generate_scope(ast_node_scope *node_scope) {
    string *ass_scope = string_create_from_cstr("");

    list *stmts = ast_node_scope_get_stmts(node_scope);
    LIST_FOR_EACH(ast_node_stmt, stmt, stmts) {
        string_concat(ass_scope, ass_gen_generate_stmt(stmt));
    }

    string *ass_scope_cleanup = string_create_from_cstr("    add rsp, ");
    string *ass_num_local_vars = string_create_from_num(sizeof(size_t) * ast_node_scope_get_num_local_vars(node_scope));

    string_concat(ass_scope, ass_scope_cleanup);
    string_concat(ass_scope_cleanup, ass_num_local_vars);
    string_concat(ass_num_local_vars, string_create_from_cstr("\n"));
    return ass_scope;
}

static string *ass_gen_generate_func(ast_node_func *node_func) {
    string *ass_func_label = string_create_from_string_view(token_get_name(ast_node_func_get_name_token(node_func)));
    string *ass_build_stack_frame = string_create_from_cstr("    push rbp\n"
                                                            "    mov rbp, rsp\n");
    string *ass_scope = ass_gen_generate_scope(ast_node_func_get_scope(node_func));
    string *ass_safety_ret = string_create_from_cstr("    mov rsp, rbp\n"
                                                     "    pop rbp\n"
                                                     "    ret\n");
    string_concat(ass_func_label, string_create_from_cstr(":\n"));
    string_concat(ass_func_label, ass_build_stack_frame);
    string_concat(ass_build_stack_frame, ass_scope);
    string_concat(ass_scope, ass_safety_ret);

    return ass_func_label;
}

string *ass_gen_generate_prog(ast_node_prog *node_prog) {
    string *ass_prog = string_create_from_cstr("    global _start\n"
                                               "_start:\n"
                                               "    call enter\n"
                                               "    mov rdi, rax\n"
                                               "    mov rax, 60\n"
                                               "    syscall\n");
    LIST_FOR_EACH(ast_node_func, func, ast_node_prog_get_funcs(node_prog)) {
        string_concat(ass_prog, ass_gen_generate_func(func));
    }

    return ass_prog;
}