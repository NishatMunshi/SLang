#include "modules/assembly_generator/ast_nodes/cond.h"

#include "modules/assembly_generator/ast_nodes/expr.h"
#include "modules/assembly_generator/ast_nodes/scope.h"

string *assembly_generator_generate_cond(ast_node_cond *node_cond) {
    string *ass_expr = assembly_generator_generate_expr(ast_node_cond_get_expr(node_cond));
    string *ass_test = string_create_from_cstr(
        "    test rax, rax\n"
        "    jz ");
    string *ass_label1 = assembly_generator_generate_new_label();
    string *ass_scope = assembly_generator_generate_scope(ast_node_cond_get_scope(node_cond));
    string *ass_label2 = string_create_from_string(ass_label1);

    string_concat(ass_expr, ass_test);
    string_concat(ass_test, ass_label1);
    string_concat(ass_label1, string_create_from_cstr("\n"));
    string_concat(ass_label1, ass_scope);
    string_concat(ass_scope, ass_label2);
    string_concat(ass_label2, string_create_from_cstr(":\n"));

    return ass_expr;
}