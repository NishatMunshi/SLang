#ifndef SLC_LIST_H
#define SLC_LIST_H

#include "list_node.h"

#include <stddef.h>

typedef struct list_struct list;

list *list_create();
void  list_push(list *list, void *data);

list_node *list_get_begin(list *list);
list_node *list_get_end(list *list);

void * list_get_back(list *list);
size_t list_get_size(list *list);

#define list_for_each(type, item, list_name) \
    list_node *node = NULL;                  \
    type *item = NULL;                       \
    for (node = list_get_begin(list_name),   \
        item = list_node_get_data(node);     \
         node != list_get_end(list_name);    \
         node = list_node_get_next(node),    \
        item = list_node_get_data(node))

void list_chop_after_and_including(list *list, list_node *list_node);

#endif // SLC_LIST_H