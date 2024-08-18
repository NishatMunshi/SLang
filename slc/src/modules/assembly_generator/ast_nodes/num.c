#include "modules/assembly_generator/ast_nodes/num.h"

string *assembly_generator_generate_num(ast_node_num *node_num) {
    string *ass_reg = string_create_from_cstr("    mov rax, ");
    string *ass_num = string_create_from_string_view(ast_node_num_get_value(node_num));

    string_concat(ass_reg, ass_num);
    string_concat(ass_num, string_create_from_cstr("\n"));

    return ass_reg;
}