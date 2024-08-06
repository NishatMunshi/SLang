#ifndef SLC_ASSEMBLY_GENERATOR_H
#define SLC_ASSEMBLY_GENERATOR_H

#include "ast_node.h"
#include "string.h"

string *ass_gen_generate_prog(ast_node_prog *node_prog);

#endif // SLC_ASSEMBLY_GENERATOR_H