#include "modules/assembly_generator/ast_nodes/un_expr.h"
#include "modules/assembly_generator/ast_nodes/num.h"
#include "modules/assembly_generator/ast_nodes/var.h"
#include "modules/assembly_generator/ast_nodes/paren_expr.h"
#include "modules/assembly_generator/ast_nodes/call.h"
#include "utils/utils.h"

string *assembly_generator_generate_un_expr(ast_node_un_expr *node_un_expr) {
    switch (ast_node_un_expr_get_type(node_un_expr)) {
    case AST_NODE_UN_EXPR_NUM: return assembly_generator_generate_num(ast_node_un_expr_get_num(node_un_expr));
    case AST_NODE_UN_EXPR_VAR: return assembly_generator_generate_var(ast_node_un_expr_get_var(node_un_expr));
    case AST_NODE_UN_EXPR_PAREN_EXPR: return assembly_generator_generate_paren_expr(ast_node_un_expr_get_paren_expr(node_un_expr));
    case AST_NODE_UN_EXPR_CALL: return assembly_generator_generate_call(ast_node_un_expr_get_call(node_un_expr));

    default: UNREACHABLE();
    }
}