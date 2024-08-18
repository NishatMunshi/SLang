#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_SCOPE_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_SCOPE_H

#include "modules/assembly_generator/assembly_generator.h"
#include "ds/ast/nodes/scope.h"

string * assembly_generator_generate_scope(ast_node_scope *node_scope);

#endif // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_SCOPE_H