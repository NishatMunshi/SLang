#ifndef SLC_STACK_NODE_H
#define SLC_STACK_NODE_H

typedef struct stack_node_struct stack_node;

stack_node* stack_node_create();

void stack_node_add_data(stack_node* node, void* data);
void stack_node_add_next(stack_node* node, stack_node* next);

void* stack_node_get_data(stack_node* node);
stack_node* stack_node_get_next(stack_node* node);

#endif // SLC_STACK_NODE_H
