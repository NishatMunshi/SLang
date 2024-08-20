#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_DECL_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_DECL_H

#include "ds/ast/nodes/decl.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_decl(ast_node_decl *node_decl);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_DECL_H
