#ifndef SLC_STACK_H
#define SLC_STACK_H

#include <stddef.h>
#include "stack_node.h"

typedef struct stack_struct stack;

stack* stack_create();
void stack_push(stack* stack, void* data);
void* stack_pop(stack* stack);
size_t stack_get_size(stack* stack);
stack_node* stack_get_top(stack* stack);

#define STACK_FOR_EACH(type, item, stack_name) \
    stack_node *STACK_FOR_EACH_NODE = NULL;                               \
    type *item = NULL;                                                  \
    for (STACK_FOR_EACH_NODE = stack_get_top(stack_name),                \
        item = stack_node_get_data(STACK_FOR_EACH_NODE);                  \
         stack_node_get_next(STACK_FOR_EACH_NODE) != NULL;                 \
         STACK_FOR_EACH_NODE = stack_node_get_next(STACK_FOR_EACH_NODE),   \
        item = stack_node_get_data(STACK_FOR_EACH_NODE))

#endif // SLC_STACK_H
