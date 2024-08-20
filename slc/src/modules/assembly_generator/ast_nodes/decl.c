#include "modules/assembly_generator/ast_nodes/decl.h"

#include "modules/assembly_generator/ast_nodes/expr.h"

string *assembly_generator_generate_decl(ast_node_decl *node_decl) {
    string *ass_expr = assembly_generator_generate_expr(ast_node_decl_get_rhs(node_decl));
    string *ass_decl = string_create_from_cstr("    push rax    ; ");
    string *ass_var_name = string_create_from_string_view(ast_node_var_get_name(ast_node_decl_get_var(node_decl)));

    string_concat(ass_expr, ass_decl);
    string_concat(ass_decl, ass_var_name);
    string_concat(ass_var_name, string_create_from_cstr("\n"));

    return ass_expr;
}