#ifndef SLC_MODULES_INPUT_OUTPUT_H
#define SLC_MODULES_INPUT_OUTPUT_H

#include "ds/string/string.h"
#include "ds/string/string_view.h"

string_view *io_read_file_into_string_view(char *file_name);
void         io_write_string_into_file(string *string, char *file_name);

#endif // SLC_MODULES_INPUT_OUTPUT_H