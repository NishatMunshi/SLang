#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PROG_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PROG_H

#include "ds/ast/nodes/prog.h"
#include "ds/string/string.h"

string *assembly_generator_generate_prog(ast_node_prog *node_prog);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_PROG_H