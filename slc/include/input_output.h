#ifndef SLC_INPUT_OUTPUT_H
#define SLC_INPUT_OUTPUT_H

#include "string.h"
#include "string_view.h"

string_view *io_read_file_into_string_view(char *file_name);
void         io_write_string_into_file(string *string, char *file_name);

#endif // SLC_INPUT_OUTPUT_H