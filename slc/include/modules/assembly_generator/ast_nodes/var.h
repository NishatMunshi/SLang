#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_VAR_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_VAR_H

#include "ds/ast/nodes/var.h"
#include "modules/assembly_generator/assembly_generator.h"

string * assembly_generator_generate_var(ast_node_var *node_var);

#endif // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_VAR_H