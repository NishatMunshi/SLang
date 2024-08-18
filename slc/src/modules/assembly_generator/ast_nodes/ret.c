#include "modules/assembly_generator/ast_nodes/ret.h"
#include "modules/assembly_generator/ast_nodes/expr.h"

string *assembly_generator_generate_ret(ast_node_ret *node_ret) {
    string *ass_expr = assembly_generator_generate_expr(ast_node_ret_get_expr(node_ret));
    string *ass_ret = string_create_from_cstr("    mov rsp, rbp\n"
                                              "    pop rbp\n"
                                              "    ret\n");

    string_concat(ass_expr, ass_ret);
    return ass_expr;
}