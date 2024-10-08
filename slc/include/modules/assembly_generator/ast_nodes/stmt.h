#ifndef SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_STMT_H
#define SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_STMT_H

#include "ds/ast/nodes/stmt.h"
#include "modules/assembly_generator/assembly_generator.h"

string *assembly_generator_generate_stmt(ast_node_stmt *node_stmt);

#endif  // SLC_MODULES_ASSEMBLY_GENERATOR_AST_NODES_STMT_H