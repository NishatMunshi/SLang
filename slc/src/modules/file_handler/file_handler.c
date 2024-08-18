#include "modules/file_handler/file_handler.h"

FILE *file_handler_open_file(char *file_name, char *mode) {
    FILE *file = fopen(file_name, mode);
    if (!file) {
        FILE_HANDLER_ERROR("could not open file \"%s\".\n", file_name);
    }
    return file;
}

