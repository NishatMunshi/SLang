#include "../include/input_output.h"
#include "../include/arena_allocator.h"
#include "../include/slc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t io_get_file_size(FILE *file) {
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return size;
}

#define IO_ERROR(...) SLC_ERROR("INPUT_OUTPUT", __VA_ARGS__)

static FILE *io_open_file(char *file_name, char *mode) {
    FILE *file = fopen(file_name, mode);
    if (!file) {
        IO_ERROR("could not open file \"%s\".\n", file_name);
    }
    return file;
}

string_view *io_read_file_into_string_view(char *file_name) {
    FILE *file = io_open_file(file_name, "r");
    size_t file_size = io_get_file_size(file);
    char *buffer = arena_allocator_allocate((file_size + 1) * sizeof(char));
    size_t size_read = fread(buffer, sizeof(char), file_size, file);
    string_view *string_view = string_view_create(buffer, size_read);
    fclose(file);
    return string_view;
}

void io_write_string_into_file(string *string, char *file_name) {
    FILE *file = io_open_file(file_name, "w");
    string_write_into_file(string, file);
    fclose(file);
}
