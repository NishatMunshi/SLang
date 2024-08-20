#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_LOOP_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_LOOP_H

#include "modules/assembly_generator/assembly_generator.h"
#include "modules/ast_verifier/ast_nodes/cond.h"

string *assembly_generator_generate_loop(ast_node_loop *node_loop);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_LOOP_H