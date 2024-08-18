#include "modules/assembly_generator/ast_nodes/paren_expr.h"
#include "modules/assembly_generator/ast_nodes/expr.h"

string *assembly_generator_generate_paren_expr(ast_node_paren_expr *node_paren_expr) {
    return assembly_generator_generate_expr(ast_node_paren_expr_get_expr(node_paren_expr));
}