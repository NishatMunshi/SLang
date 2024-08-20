#ifndef SLC_MODULES_FILE_HANDLER_FILE_HANDLER_H
#define SLC_MODULES_FILE_HANDLER_FILE_HANDLER_H

#include <stdio.h>

#include "ui/ui.h"

#define FILE_HANDLER_ERROR(...) UI_ERROR("FILE_HANDLER", __VA_ARGS__)

FILE *file_handler_open_file(char *file_name, char *mode);

#endif  // SLC_MODULES_FILE_HANDLER_FILE_HANDLER_H