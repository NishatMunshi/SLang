#include "modules/assembly_generator/ast_nodes/scope.h"

#include "modules/assembly_generator/ast_nodes/stmt.h"

string *assembly_generator_generate_scope(ast_node_scope *node_scope) {
    string *ass_scope = string_create_from_cstr("");

    list *stmts = ast_node_scope_get_stmts(node_scope);
    LIST_FOR_EACH(ast_node_stmt, stmt, stmts) {
        string_concat(ass_scope, assembly_generator_generate_stmt(stmt));
    }

    string *ass_scope_cleanup = string_create_from_cstr("    add rsp, ");
    string *ass_num_local_vars = string_create_from_num(sizeof(size_t) * ast_node_scope_get_num_local_vars(node_scope));

    string_concat(ass_scope, ass_scope_cleanup);
    string_concat(ass_scope_cleanup, ass_num_local_vars);
    string_concat(ass_num_local_vars, string_create_from_cstr("\n"));
    return ass_scope;
}
