#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_EXPR_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_EXPR_H

#include "ds/ast/nodes/expr.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_expr(ast_node_expr *node_expr);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_EXPR_H
