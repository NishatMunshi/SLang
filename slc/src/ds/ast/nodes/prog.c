#include "ds/ast/nodes/prog.h"

#include "memory/arena_allocator.h"

struct ast_node_prog_struct {
    list *funcs;
};

ast_node_prog *ast_node_prog_create(list *funcs_list) {
    ast_node_prog *node_prog = arena_allocator_allocate(sizeof(struct ast_node_prog_struct));
    node_prog->funcs = funcs_list;
    return node_prog;
}

list *ast_node_prog_get_funcs(ast_node_prog *node_prog) {
    return node_prog->funcs;
}
