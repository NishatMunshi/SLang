#include "modules/file_handler/helpers/writer.h"
#include "modules/file_handler/file_handler.h"

void writer_write_string_into_file(string *string, char *file_name) {
    FILE *file = file_handler_open_file(file_name, "w");
    string_write_into_file(string, file);
    fclose(file);
}
