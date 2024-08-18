#include "modules/assembly_generator/ast_nodes/expr.h"
#include "modules/assembly_generator/ast_nodes/un_expr.h"
#include "modules/assembly_generator/ast_nodes/bin_expr.h"
#include "utils/utils.h"

string *assembly_generator_generate_expr(ast_node_expr *node_expr) {
    switch (ast_node_expr_get_type(node_expr)) {
    case AST_NODE_EXPR_UN_EXPR: return assembly_generator_generate_un_expr(ast_node_expr_get_un_expr(node_expr));
    case AST_NODE_EXPR_BIN_EXPR: return assembly_generator_generate_bin_expr(ast_node_expr_get_bin_expr(node_expr));

    default: UNREACHABLE();
    }
}
