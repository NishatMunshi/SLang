#ifndef SLC_LIST_NODE_H
#define SLC_LIST_NODE_H

typedef struct list_node_struct list_node;

list_node *list_node_create();

void list_node_add_data(list_node *node, void *data);
void list_node_add_next(list_node *node, list_node *next);

void *     list_node_get_data(list_node *node);
list_node *list_node_get_next(list_node *node);

#endif // SLC_LIST_NODE_H