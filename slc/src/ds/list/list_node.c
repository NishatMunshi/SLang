#include "ds/list/list_node.h"

#include <stdio.h>
#include <stdlib.h>

#include "memory/arena_allocator.h"

struct list_node_struct {
    void *data;
    struct list_node_struct *next;
};

list_node *list_node_create() {
    return arena_allocator_allocate(sizeof(struct list_node_struct));
}

void list_node_add_data(list_node *node, void *data) {
    node->data = data;
}

void list_node_add_next(list_node *node, list_node *next) {
    node->next = next;
}

void *list_node_get_data(list_node *node) {
    return node->data;
}

list_node *list_node_get_next(list_node *node) {
    return node->next;
}
