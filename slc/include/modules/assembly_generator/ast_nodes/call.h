#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_CALL_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_CALL_H

#include "modules/assembly_generator/assembly_generator.h"
#include "ds/ast/nodes/call.h"

string * assembly_generator_generate_call(ast_node_call *node_call);

#endif // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_CALL_H