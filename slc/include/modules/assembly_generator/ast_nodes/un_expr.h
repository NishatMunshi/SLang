#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_UN_EXPR_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_UN_EXPR_H

#include "ds/ast/nodes/un_expr.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_un_expr(ast_node_un_expr *node_un_expr);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_UN_EXPR_H