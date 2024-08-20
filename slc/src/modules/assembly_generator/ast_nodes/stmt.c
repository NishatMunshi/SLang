#include "modules/assembly_generator/ast_nodes/stmt.h"

#include "modules/assembly_generator/ast_nodes/asst.h"
#include "modules/assembly_generator/ast_nodes/cond.h"
#include "modules/assembly_generator/ast_nodes/decl.h"
#include "modules/assembly_generator/ast_nodes/loop.h"
#include "modules/assembly_generator/ast_nodes/ret.h"
#include "utils/utils.h"

string *assembly_generator_generate_stmt(ast_node_stmt *node_stmt) {
    switch (ast_node_stmt_get_type(node_stmt)) {
        case AST_NODE_STMT_DECL:
            return assembly_generator_generate_decl(ast_node_stmt_get_decl(node_stmt));
        case AST_NODE_STMT_ASST:
            return assembly_generator_generate_asst(ast_node_stmt_get_asst(node_stmt));
        case AST_NODE_STMT_COND:
            return assembly_generator_generate_cond(ast_node_stmt_get_cond(node_stmt));
        case AST_NODE_STMT_LOOP:
            return assembly_generator_generate_loop(ast_node_stmt_get_loop(node_stmt));
        case AST_NODE_STMT_RET:
            return assembly_generator_generate_ret(ast_node_stmt_get_ret(node_stmt));

        default:
            UNREACHABLE();
    }
}
