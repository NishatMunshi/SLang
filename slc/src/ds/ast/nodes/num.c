#include "ds/ast/nodes/num.h"
#include "memory/arena_allocator.h"

struct ast_node_num_struct {
    string_view *num_value;
};

ast_node_num *ast_node_num_create(string_view *num_value) {
    ast_node_num *node_num = arena_allocator_allocate(sizeof(struct ast_node_num_struct));
    node_num->num_value = num_value;

    return node_num;
}

string_view *ast_node_num_get_value(ast_node_num *node_num) {
    return node_num->num_value;
}