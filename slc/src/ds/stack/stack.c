#include "ds/stack/stack.h"
#include "memory/arena_allocator.h"

struct stack_struct {
    stack_node *top;
    size_t size;
};

stack* stack_create() {
    stack *stack = arena_allocator_allocate(sizeof(struct stack_struct));
    stack->top = stack_node_create();
    stack->size = 0;
    
    return stack;
}

void stack_push(stack* stack, void* data) {
    stack_node *new_node = stack_node_create();
    stack_node *old_top = stack->top;
    stack_node_add_data(new_node, data);
    stack_node_add_next(new_node, old_top);
    stack->top = new_node;
    stack->size++;
}

void* stack_pop(stack* stack) {
    stack_node *old_top = stack->top;
    stack->top = stack_node_get_next(stack->top);
    stack->size--;
    return stack_node_get_data(old_top);
}

size_t stack_get_size(stack* stack) {
    return stack->size;
}

stack_node* stack_get_top(stack* stack) {
    return stack->top;
}
