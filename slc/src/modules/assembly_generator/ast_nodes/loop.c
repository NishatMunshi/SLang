#include "modules/assembly_generator/ast_nodes/loop.h"
#include "modules/assembly_generator/ast_nodes/scope.h"
#include "modules/assembly_generator/ast_nodes/expr.h"

string *assembly_generator_generate_loop(ast_node_loop *node_loop) {
    string *ass_loop_label = assembly_generator_generate_new_label();
    string *ass_expr = assembly_generator_generate_expr(ast_node_loop_get_expr(node_loop));
    string *ass_test = string_create_from_cstr("    test rax, rax\n"
                                               "    jz ");
    string *ass_skip_label = assembly_generator_generate_new_label();
    string *ass_scope = assembly_generator_generate_scope(ast_node_loop_get_scope(node_loop));
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