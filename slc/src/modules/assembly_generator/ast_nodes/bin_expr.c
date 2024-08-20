#include "modules/assembly_generator/ast_nodes/bin_expr.h"

#include "modules/assembly_generator/ast_nodes/expr.h"
#include "modules/assembly_generator/ast_nodes/un_expr.h"
#include "utils/utils.h"

string *assembly_generator_generate_bin_expr(ast_node_bin_expr *node_bin_expr) {
    string *ass_left_expr = assembly_generator_generate_expr(ast_node_bin_expr_get_left(node_bin_expr));
    string *ass_save_rax = string_create_from_cstr("    push rax\n");
    string *ass_right_expr = assembly_generator_generate_un_expr(ast_node_bin_expr_get_right(node_bin_expr));
    string *ass_load_saved_rax = string_create_from_cstr(
        "    mov rbx, rax\n"
        "    pop rax\n");
    string *ass_instruction = NULL;
    switch (ast_node_bin_expr_get_type(node_bin_expr)) {
        case AST_NODE_BIN_EXPR_ADD:
            ass_instruction = string_create_from_cstr("    add rax, rbx\n");
            break;
        case AST_NODE_BIN_EXPR_SUB:
            ass_instruction = string_create_from_cstr("    sub rax, rbx\n");
            break;

        default:
            UNREACHABLE();
    }

    string_concat(ass_left_expr, ass_save_rax);
    string_concat(ass_save_rax, ass_right_expr);
    string_concat(ass_right_expr, ass_load_saved_rax);
    string_concat(ass_load_saved_rax, ass_instruction);

    return ass_left_expr;
}
