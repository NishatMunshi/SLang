#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PAREN_EXPR_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PAREN_EXPR_H

#include "ds/ast/nodes/paren_expr.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_paren_expr(ast_node_paren_expr *node_paren_expr);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PAREN_EXPR_H