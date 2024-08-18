#include "modules/assembly_generator/assembly_generator.h"
#include "memory/arena_allocator.h"
#include "utils/utils.h"

#include <string.h>

string *assembly_generator_generate_new_label() {
    static size_t label = 0;
    char *template = "label%zu";
    char *cstr = arena_allocator_allocate(strlen(template) + utils_count_digits_in_num(label));
    sprintf(cstr, template, label++);
    string *ass_label = string_create_from_cstr(cstr);
    return ass_label;
}