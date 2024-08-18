#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_COND_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_COND_H

#include "modules/assembly_generator/assembly_generator.h"
#include "ds/ast/nodes/cond.h"

string * assembly_generator_generate_cond(ast_node_cond *node_cond);

#endif // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_COND_H