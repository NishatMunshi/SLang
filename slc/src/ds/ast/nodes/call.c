#include "ds/ast/nodes/call.h"
#include "memory/arena_allocator.h"

struct ast_node_call_struct {
    token *name;
    list *args;
};

ast_node_call *ast_node_call_create(token *name, list *args) {
    ast_node_call *node_call = arena_allocator_allocate(sizeof(struct ast_node_call_struct));
    node_call->name = name;
    node_call->args = args;

    return node_call;
}

token *ast_node_call_get_name(ast_node_call *node_call) { 
    return node_call->name;
}

list *ast_node_call_get_args(ast_node_call *node_call) { 
    return node_call->args; 
}
