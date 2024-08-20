#ifndef SLC_MODULES_FILE_HANDLER_HELPERS_READER_H
#define SLC_MODULES_FILE_HANDLER_HELPERS_READER_H

#include "ds/string/string_view.h"

string_view *reader_read_file_into_string_view(char *file_name);

#endif  // SLC_MODULES_FILE_HANDLER_HELPERS_READER_H