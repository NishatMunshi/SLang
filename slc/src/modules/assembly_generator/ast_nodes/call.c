#include "modules/assembly_generator/ast_nodes/call.h"
#include "modules/assembly_generator/ast_nodes/expr.h"
#include "ds/ast/nodes/expr.h"

string *assembly_generator_generate_call(ast_node_call *node_call) {
    string *ass_call = string_create_from_cstr("");
    LIST_FOR_EACH(ast_node_expr, expr, ast_node_call_get_args(node_call)) {
        string *ass_expr = assembly_generator_generate_expr(expr);
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