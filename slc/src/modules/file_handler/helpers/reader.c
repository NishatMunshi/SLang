#include "modules/file_handler/helpers/reader.h"
#include "modules/file_handler/file_handler.h"
#include "memory/arena_allocator.h"

static size_t reader_get_file_size(FILE *file) {
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return size;
}

string_view *reader_read_file_into_string_view(char *file_name) {
    FILE *file = file_handler_open_file(file_name, "r");
    size_t file_size = reader_get_file_size(file);
    char *buffer = arena_allocator_allocate((file_size + 1) * sizeof(char));
    size_t size_read = fread(buffer, sizeof(char), file_size, file);
    string_view *string_view = string_view_create(buffer, size_read);
    fclose(file);
    return string_view;
}
