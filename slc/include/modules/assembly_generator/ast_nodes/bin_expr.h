#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_BIN_EXPR_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_BIN_EXPR_H

#include "modules/assembly_generator/assembly_generator.h"
#include "ds/ast/nodes/bin_expr.h"

string * assembly_generator_generate_bin_expr(ast_node_bin_expr *node_bin_expr);

#endif // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_BIN_EXPR_H