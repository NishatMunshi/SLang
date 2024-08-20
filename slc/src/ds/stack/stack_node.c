#include "ds/stack/stack_node.h"

#include "memory/arena_allocator.h"

struct stack_node_struct {
    void* data;
    struct stack_node_struct* next;
};

stack_node* stack_node_create() {
    stack_node* node = arena_allocator_allocate(sizeof(struct stack_node_struct));
    node->data = NULL;
    node->next = NULL;

    return node;
}

void stack_node_add_data(stack_node* node, void* data) {
    node->data = data;
}

void stack_node_add_next(stack_node* node, stack_node* next) {
    node->next = next;
}

void* stack_node_get_data(stack_node* node) {
    return node->data;
}

stack_node* stack_node_get_next(stack_node* node) {
    return node->next;
}