#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_RET_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_RET_H

#include "ds/ast/nodes/ret.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_ret(ast_node_ret *node_ret);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_RET_H