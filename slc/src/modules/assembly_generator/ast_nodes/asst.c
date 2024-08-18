#include "modules/assembly_generator/ast_nodes/asst.h"
#include "modules/assembly_generator/ast_nodes/expr.h"

string *assembly_generator_generate_asst(ast_node_asst *node_asst) {
    string *ass_expr = assembly_generator_generate_expr(ast_node_asst_get_rhs(node_asst));
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