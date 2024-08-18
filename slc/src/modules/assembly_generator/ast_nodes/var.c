#include "modules/assembly_generator/ast_nodes/var.h"

string *assembly_generator_generate_var(ast_node_var *node_var) {
    string *ass_reg = string_create_from_cstr("    mov rax, ");
    string *ass_var = string_create_from_cstr("[rbp + (");
    string *ass_offset = string_create_from_num(ast_node_var_get_offset(node_var));
    string *ass_square_bracket = string_create_from_cstr(")]\n");

    string_concat(ass_reg, ass_var);
    string_concat(ass_var, ass_offset);
    string_concat(ass_offset, ass_square_bracket);

    return ass_reg;
}