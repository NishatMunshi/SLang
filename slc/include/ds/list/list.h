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

#define LIST_FOR_EACH(type, item, list_name)                            \
    list_node *LIST_FOR_EACH_NODE = NULL;                               \
    type *item = NULL;                                                  \
    for (LIST_FOR_EACH_NODE = list_get_begin(list_name),                \
        item = list_node_get_data(LIST_FOR_EACH_NODE);                  \
         LIST_FOR_EACH_NODE != list_get_end(list_name);                 \
         LIST_FOR_EACH_NODE = list_node_get_next(LIST_FOR_EACH_NODE),   \
        item = list_node_get_data(LIST_FOR_EACH_NODE))

void list_chop_after_and_including(list *list, list_node *list_node);

#endif // SLC_LIST_H