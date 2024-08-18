#include "modules/assembly_generator/ast_nodes/func.h"
#include "modules/assembly_generator/ast_nodes/scope.h"

string *assembly_generator_generate_func(ast_node_func *node_func) {
    string *ass_func_label = string_create_from_string_view(token_get_name(ast_node_func_get_name_token(node_func)));
    string *ass_build_stack_frame = string_create_from_cstr("    push rbp\n"
                                                            "    mov rbp, rsp\n");
    string *ass_scope = assembly_generator_generate_scope(ast_node_func_get_scope(node_func));
    string *ass_safety_ret = string_create_from_cstr("    mov rsp, rbp\n"
                                                     "    pop rbp\n"
                                                     "    ret\n");
    string_concat(ass_func_label, string_create_from_cstr(":\n"));
    string_concat(ass_func_label, ass_build_stack_frame);
    string_concat(ass_build_stack_frame, ass_scope);
    string_concat(ass_scope, ass_safety_ret);

    return ass_func_label;
}