#include "../include/slc.h"
#include "../include/arena_allocator.h"
#include "../include/assembly_generator.h"
#include "../include/ast_verifier.h"
#include "../include/input_output.h"
#include "../include/lexer.h"
#include "../include/parser.h"

#include <stdlib.h>

struct slc_struct {
    char *compiler_executable_name;
    char *source_file_name;
    char *output_file_name;
};

static struct slc_struct *slc = NULL;

void slc_init(char *compiler_executable_name) {
    arena_allocator_init();
    slc = arena_allocator_allocate(sizeof(struct slc_struct));
    slc->compiler_executable_name = compiler_executable_name;
}

void slc_print_usage() { 
    slc_print_compiler_execuatable_name();
    printf("[USAGE]: %s <source filename> <output filename>\n", slc->compiler_executable_name);
}

void slc_print_error_and_exit(char *message) {
    slc_print_compiler_execuatable_name();
    printf("%s\n", message);
    exit(1);
}

void slc_compile(char *source_file_name, char *output_file_name) {
    slc->source_file_name = source_file_name;
    slc->output_file_name = output_file_name;
    
    string_view *source_code = io_read_file_into_string_view(source_file_name);
    list *token_list = lexer_lex(source_code);
    ast_node_prog *node_prog = parser_parse_prog(token_list);
    ast_verifier_verify_prog(node_prog);
    string *assembly = ass_gen_generate_prog(node_prog);
    io_write_string_into_file(assembly, output_file_name);
}

void slc_print_source_file_name() {
    printf("%s", slc->source_file_name);
    printf(":");
}

void slc_print_compiler_execuatable_name() {
    printf("[SLC]: ");
}
