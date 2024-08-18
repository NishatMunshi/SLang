#include "slc/slc.h"
#include "ui/ui.h"
#include "memory/arena_allocator.h"
#include "modules/assembly_generator.h"
#include "modules/ast_verifier.h"
#include "modules/input_output.h"
#include "modules/lexer.h"
#include "modules/parser/prog.h"

#include <stdlib.h>

static struct slc_struct {
    char *compiler_executable_name;
    char *source_file_name;
    char *output_file_name;
} slc = {0};

void slc_compile(char *compiler_executable_name, char *source_file_name, char *output_file_name) {
    slc.compiler_executable_name = compiler_executable_name;
    slc.source_file_name = source_file_name;
    slc.output_file_name = output_file_name;
    
    string_view *source_code = io_read_file_into_string_view(source_file_name);
    list *token_list = lexer_lex(source_code);
    ast_node_prog *node_prog = parser_parse_prog(token_list);
    ast_verifier_verify_prog(node_prog);
    string *assembly = ass_gen_generate_prog(node_prog);
    io_write_string_into_file(assembly, output_file_name);
}

char *slc_get_source_file_name() {
    return slc.source_file_name;
}
