#include "modules/assembly_generator/ast_nodes/prog.h"
#include "modules/assembly_generator/ast_nodes/func.h"
#include "ds/string/string.h"
#include "ds/ast/nodes/func.h"

string *assembly_generator_generate_prog(ast_node_prog *node_prog) {
    string *ass_prog = string_create_from_cstr("    global _start\n"
                                               "_start:\n"
                                               "    call enter\n"
                                               "    mov rdi, rax\n"
                                               "    mov rax, 60\n"
                                               "    syscall\n");
    LIST_FOR_EACH(ast_node_func, func, ast_node_prog_get_funcs(node_prog)) {
        string_concat(ass_prog, assembly_generator_generate_func(func));
    }

    return ass_prog;
}