#include "../include/list.h"
#include "../include/arena_allocator.h"

#include <stdio.h>
#include <stdlib.h>

struct list_struct {
    list_node *begin;
    list_node *end;
    list_node *back;
    size_t size;
};

list *list_create() {
    list *list = arena_allocator_allocate(sizeof(struct list_struct));
    list->begin = list->end = list_node_create();
    list->back = NULL;
    list->size = 0;
    return list;
}

void list_push(list *list, void *data) {
    list_node_add_data(list->end, data);
    list_node *new_node = list_node_create();
    list_node_add_next(list->end, new_node);
    list->back = list->end;
    list->end = new_node;
    list->size++;
}

list_node *list_get_begin(list *list) {
    return list->begin;
}

list_node *list_get_end(list *list) {
    return list->end;
}

size_t list_get_size(list *list) {
    return list->size;
}

void list_chop_after_and_including(list *list, list_node *end_node) {
    list->end = end_node;
    list->size = 0;
    LIST_FOR_EACH(char , list_node, list) {
        list->size++;
        (void)list_node;
    }
}

void *list_get_back(list *list) {
    return list->back ? list_node_get_data(list->back) : NULL;
}
